#include "CameraComponent.h"
#include <GLFW/glfw3.h>
#include "GameObject.h"

CameraComponent::CameraComponent(GLFWwindow* window) 
	: window(window), fov(75.f)
{
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	if (glfwRawMouseMotionSupported()) {
		glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
	}
}

CameraComponent::~CameraComponent()
{
}

glm::mat4 CameraComponent::getMatrix()
{
	glm::mat4 ret(1.0f);
	ret = glm::rotate(ret, gameObject->rotation.x, glm::vec3(1, 0, 0));
	ret = glm::rotate(ret, gameObject->rotation.y, glm::vec3(0, 1, 0));
	ret = glm::translate(ret, gameObject->position);
	return ret;
}

void CameraComponent::update(float deltaTime)
{
	updateCamera(deltaTime);
}

void CameraComponent::updateCamera(float deltaTime) {
	double x, y;
	glfwGetCursorPos(window, &x, &y);

	static double lastX = x;
	static double lastY = y;

	float tempX = gameObject->rotation.x - (float)(lastY - y) / 100.f;

	if (tempX < 0.9f && tempX > -0.7f)
		gameObject->rotation.x = tempX;

	gameObject->rotation.y -= (float)(lastX - x) / 100.f;

	lastX = x;
	lastY = y;
}

void CameraComponent::changeFOV(float deltaTime, bool running)
{
	if(running) {
	if (fov < 100.f) {
			fov += 50.f * deltaTime;
		}
	}
	else {
		if (fov > 75.f) {
			fov -= 50.f * deltaTime;
		}
	}
}
