#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "tigl.h"
#include <glm/gtc/matrix_transform.hpp>

#include "MazeGenerator.h"

#include "GameObject.h"
#include "CubeComponent.h"
#include "PlayerComponent.h"
#include "CameraComponent.h"
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

	mazeGen = new MazeGenerator();
	auto maze = mazeGen->Generate(10, 10);

	player = std::make_shared<GameObject>();
	player->position = mazeGen->spawnPoint;

	player->addComponent(std::make_shared<PlayerComponent>(window));
	player->addComponent(std::make_shared<CameraComponent>(window));

	for (auto row : maze) {
		for (auto obj : row) {
			objects.push_back(std::make_shared<GameObject>(obj->gameObject));
		}
	}
}

void update()
{
	double currentFrame = glfwGetTime();
	float deltaTime = currentFrame - lastFrameTime;
	lastFrameTime = currentFrame;

	for (auto& o : objects)
		o->update((float)deltaTime);

	player->update(deltaTime);
	auto cameraComponent = player->getComponent<CameraComponent>();
	if (player->getComponent<PlayerComponent>()->bIsRunning) {
		cameraComponent->changeFOV(deltaTime, true);
	}
	else {
		cameraComponent->changeFOV(deltaTime, false);
	}
}

void draw()
{
	glClearColor(0.3f, 0.4f, 0.6f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);

	int viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	auto cameraComponent = player->getComponent<CameraComponent>();

	glm::mat4 projection = glm::perspective(glm::radians(player->getComponent<CameraComponent>()->fov), viewport[2] / (float)viewport[3], 0.01f, 1000.0f);

	tigl::shader->setProjectionMatrix(projection);
	tigl::shader->setViewMatrix(cameraComponent->getMatrix());
	tigl::shader->setModelMatrix(glm::mat4(1.0f));

	tigl::shader->enableColor(true);

	for (auto& o : objects)
		o->draw();
}