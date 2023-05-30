#include "PlayerComponent.h"
#include "GameObject.h"
#include <GLFW/glfw3.h>

PlayerComponent::PlayerComponent(GLFWwindow* window, float speed)
	: window(window), speed(speed), bIsRunning(false)
{

}

PlayerComponent::~PlayerComponent()
{

}

void PlayerComponent::move(float angle, float fac, float deltaTime)
{
	gameObject->position.x += (float)cos(gameObject->rotation.y + glm::radians(angle)) * fac * speed * deltaTime;
	gameObject->position.z += (float)sin(gameObject->rotation.y + glm::radians(angle)) * fac * speed * deltaTime;
}

void PlayerComponent::update(float deltaTime)
{
	playerInput(deltaTime);
}

void PlayerComponent::playerInput(float deltaTime)
{
	float multi = 1.f;
	// multiplier for running
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
		multi *= 3.f;
		bShiftPressed = true;
	}
	else
		bShiftPressed = false;

	// forward
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		move(90, 0.05f * multi, deltaTime);
		bWPressed = true;
	}
	else
		bWPressed = false;

	// backward
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		move(-90, 0.05f, deltaTime);

	// left
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		move(0, 0.05f, deltaTime);

	// right
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		move(180, 0.05f, deltaTime);

	// up
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		gameObject->position.y -= speed * 0.001f;
	}

	// down
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		gameObject->position.y += speed * 0.001f;
	}

	// isRunning
	if (bWPressed && bShiftPressed) {
		bIsRunning = true;
	}
	else {
		bIsRunning = false;
	}
}

