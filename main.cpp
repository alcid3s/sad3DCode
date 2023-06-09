// first include because it contains ImGui
#include "GuiManager.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "tigl.h"
#include <glm/gtc/matrix_transform.hpp>
#include "MazeGenerator.h"
#include "GameObject.h"
#include "CubeComponent.h"
#include "PlayerComponent.h"
#include "CameraComponent.h"
#include "AudioComponent.h"
#include "FlashlightComponent.h"
#include "BoundingBoxComponent.h"
#include "EnemyComponent.h"
#include "AltarComponent.h"
#include "HUDComponent.h"
#include <memory>

#include <thread>
#include <atomic>

#include <iostream>
using tigl::Vertex;

#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "opengl32.lib")

// used to communicate between threads.
std::atomic<bool> bMazeGenerated(false);
bool bMazeGenerationStarted = false;

GLFWwindow* window;

std::shared_ptr<GameObject> player;
std::list<std::shared_ptr<GameObject>> objects;

MazeGenerator* mazeGen;

GuiManager* guiManager;

double lastFrameTime = 0;

const bool activateGui = false;

const int screenX = 1400, screenY = 800;

void init();
void update();
void draw();
void updatePlayer(float deltaTime);
void enableFog(bool flag);

int main(void)
{
	if (!glfwInit())
		throw "Could not initialize glwf";
	window = glfwCreateWindow(screenX, screenY, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		throw "Could not initialize glwf";
	}
	glfwMakeContextCurrent(window);

	tigl::init();

	if (activateGui) {
		guiManager = new GuiManager(window, screenX, screenY);
		guiManager->init();
	}
	else {
		init();
	}

	while (!glfwWindowShouldClose(window))
	{
		update();
		draw();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}

// This function will run in a seperate thread
void init()
{
	glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			if (key == GLFW_KEY_ESCAPE)
				glfwSetWindowShouldClose(window, true);
		});

	// Initialise and draw a maze
	mazeGen = new MazeGenerator();
	auto maze = mazeGen->Generate(10, 10);

	// Adding all gameobjects the generate function created to the gameobjects list
	for (auto row : maze) {
		for (auto obj : row) {
			if (obj->gameObject.type == Type::Wall || obj->gameObject.type == Type::Edge) {
				glm::vec3 minimal = glm::vec3(-.5f, 0, -.5f);
				glm::vec3 maximal = glm::vec3(.5f, 0, .5f);
				obj->gameObject.addComponent(std::make_shared<BoundingBoxComponent>(minimal, maximal));
			}
			objects.push_back(std::make_shared<GameObject>(obj->gameObject));
		}
	}

	// Create player and sets it's position to the spawnpoint
	player = std::make_shared<GameObject>();
	player->type = Type::Player;
	player->position = mazeGen->spawnPoint;

	// Adding components to the player
	player->addComponent(std::make_shared<PlayerComponent>(window));
	player->addComponent(std::make_shared<CameraComponent>(window));
	player->addComponent(std::make_shared<AudioComponent>(AudioType::AudioPlayer));
	player->addComponent(std::make_shared<FlashlightComponent>());
	player->addComponent(std::make_shared<HUDComponent>());

	glm::vec3 min = glm::vec3(-.1f, 0, -.1f);
	glm::vec3 max = glm::vec3(.1f, 0, .1f);
	player->addComponent(std::make_shared<BoundingBoxComponent>(min, max));

	// Creating an enemy and adding it to the objects list
	auto enemy = std::make_shared<GameObject>();
	enemy->position = mazeGen->enemySpawnTile->position;
	enemy->addComponent(std::make_shared<EnemyComponent>(objects));
	objects.push_back(enemy);

	// adding ambient sound to the objects list
	auto ambience = std::make_shared<GameObject>();
	ambience->addComponent(std::make_shared<AudioComponent>(AudioType::Ambience));
	objects.push_back(ambience);

	// adding the endpoint object to the game. Y position -.499 so it stands directly on the floor
	auto altar = std::make_shared<GameObject>();
	altar->position = mazeGen->endPoint;
	altar->position.y = -.499f;
	altar->addComponent(std::make_shared<AltarComponent>());
	objects.push_back(altar);

	bMazeGenerated = true;
}

// Enables fog into the world
void enableFog(bool flag) {
	if (flag) {
		tigl::shader->enableFog(true);
		tigl::shader->setFogColor(glm::vec3(.05f, .05f, .05f));
		tigl::shader->setFogLinear(1, 4);
		tigl::shader->setFogExp(1.5f);
	}
	else {
		tigl::shader->enableFog(false);
	}
}

// Functions to update the player
void updatePlayer(float deltaTime) {
	// getting player component
	auto playerComponent = player->getComponent<PlayerComponent>();

	// updating player
	player->update(deltaTime);

	// checking collision of player. If no collision occurs move is validated.
	playerComponent->checkCollision(objects);

	// Getting the rest of the components
	auto cameraComponent = player->getComponent<CameraComponent>();
	auto audioComponent = player->getComponent<AudioComponent>();
	auto flashlightComponent = player->getComponent<FlashlightComponent>();

	// Letting the audio component know if there've been updates concerning the movement of the player
	audioComponent->bIsRunning = playerComponent->bIsRunning;
	audioComponent->bIsMoving = playerComponent->bMoving;
	audioComponent->bPlayOutOfBreathSound = playerComponent->bPlayOutOfBreathSound;

	// let flashLight know if player is running
	flashlightComponent->bIsRunning = playerComponent->bIsRunning;

	//hudComponent->setRotation(cameraComponent->)

	// Change FOV according to the movement of the player
	cameraComponent->changeFOV(deltaTime, playerComponent->bIsRunning);
}

void update()
{
	if (activateGui) {
		if (guiManager->menuType == MenuType::MainMenu) {
			guiManager->update();
			return;
		}
		else if (guiManager->menuType == MenuType::Loading && !bMazeGenerationStarted) {
			// setting to false if it was true
			bMazeGenerated = false;

			// maze generation ahs started so it won't start another time
			bMazeGenerationStarted = true;

			// creating thread initialising all variables
			std::thread initThread(init);

			// detach so mainthread can run normally.
			initThread.detach();
		}
		if (!bMazeGenerated) {
			return;
		}
		else {
			guiManager->menuType = MenuType::Playing;
		}
	}

	// Getting deltatime
	double currentFrame = glfwGetTime();
	float deltaTime = currentFrame - lastFrameTime;
	lastFrameTime = currentFrame;
		
	// Updating gameobjects
	for (auto& o : objects)
		o->update(deltaTime);

	// Updating player
	updatePlayer(deltaTime);
}

void draw()
{
	if (activateGui) {
		if (guiManager->menuType == MenuType::MainMenu) {
			guiManager->draw();
			return;
		}
		else if (guiManager->menuType == MenuType::Loading) {
			guiManager->draw();
			return;
		}
		if (!bMazeGenerated) {
			return;
		}
	}
	
	// Draw dark background
	glClearColor(.05f, .05f, .05f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Make sure not all sides of the vertices are visible to the player
	glEnable(GL_DEPTH_TEST);

	// Set projection matrix
	int viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	
	glm::mat4 projection = glm::perspective(glm::radians(player->getComponent<CameraComponent>()->fov), viewport[2] / (float)viewport[3], 0.01f, 1000.0f);

	auto cameraComponent = player->getComponent<CameraComponent>();

	// Setting matrixes
	tigl::shader->setProjectionMatrix(projection);
	tigl::shader->setViewMatrix(cameraComponent->getMatrix());
	tigl::shader->setModelMatrix(glm::mat4(1.0f));

	tigl::shader->enableColor(true);

	enableFog(true);

	// Drawing all gameobjects
	for (auto& o : objects)
		o->draw();

	// Drawing the flashlight and HUD of the player
	player->getComponent<FlashlightComponent>()->draw();
	if (!activateGui) {
		player->getComponent<HUDComponent>()->draw();
	}
	
}