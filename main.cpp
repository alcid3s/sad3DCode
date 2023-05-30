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
#include <memory>

using tigl::Vertex;

#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "opengl32.lib")

GLFWwindow* window;

std::shared_ptr<GameObject> player;
std::list<std::shared_ptr<GameObject>> objects;
MazeGenerator* mazeGen;
double lastFrameTime = 0;

void init();
void update();
void draw();
void updatePlayer(float deltaTime);

int main(void)
{
	if (!glfwInit())
		throw "Could not initialize glwf";
	window = glfwCreateWindow(1400, 800, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		throw "Could not initialize glwf";
	}
	glfwMakeContextCurrent(window);

	tigl::init();

	init();

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

	// Create player and sets it's position to the spawnpoint
	player = std::make_shared<GameObject>();
	player->position = mazeGen->spawnPoint;

	// Adding components to the player
	player->addComponent(std::make_shared<PlayerComponent>(window));
	player->addComponent(std::make_shared<CameraComponent>(window));
	player->addComponent(std::make_shared<AudioComponent>(AudioType::Footsteps));

	// Adding all gameobjects the generate function created to the gameobjects list
	for (auto row : maze) {
		for (auto obj : row) {
			objects.push_back(std::make_shared<GameObject>(obj->gameObject));
		}
	}
}

// Functions to update the player
void updatePlayer(float deltaTime) {
	player->update(deltaTime);

	// Getting components
	auto cameraComponent = player->getComponent<CameraComponent>();
	auto playerComponent = player->getComponent<PlayerComponent>();
	auto audioComponent = player->getComponent<AudioComponent>();

	// Letting the audio component know if there've been updates concerning the movement of the player
	audioComponent->bIsRunning = playerComponent->bIsRunning;
	audioComponent->bIsMoving = playerComponent->bMoving;

	// Change FOV according to the movement of the player
	cameraComponent->changeFOV(deltaTime, playerComponent->bIsRunning);
}

void update()
{
	// Getting deltatime
	double currentFrame = glfwGetTime();
	float deltaTime = currentFrame - lastFrameTime;
	lastFrameTime = currentFrame;

	// Updating gameobjects
	for (auto& o : objects)
		o->update((float)deltaTime);

	// Updating player
	updatePlayer(deltaTime);
}

void draw()
{
	// Draw dark background
	glClearColor(0.05f, 0.05f, 0.05f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Make sure not all sides of the vertices are visible to the player
	glEnable(GL_DEPTH_TEST);

	// Set projection matrix
	int viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	auto cameraComponent = player->getComponent<CameraComponent>();

	glm::mat4 projection = glm::perspective(glm::radians(player->getComponent<CameraComponent>()->fov), viewport[2] / (float)viewport[3], 0.01f, 1000.0f);

	// Setting matrixes
	tigl::shader->setProjectionMatrix(projection);
	tigl::shader->setViewMatrix(cameraComponent->getMatrix());
	tigl::shader->setModelMatrix(glm::mat4(1.0f));

	tigl::shader->enableColor(true);

	// Drawing all gameobjects
	for (auto& o : objects)
		o->draw();
}