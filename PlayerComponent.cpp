#include "PlayerComponent.h"
#include "GameObject.h"
#include <GLFW/glfw3.h>

PlayerComponent::PlayerComponent(GLFWwindow* window, float speed) 
	: window(window), speed(speed)
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
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		move(90, 0.05f, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		move(-90, 0.05f, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		move(0, 0.05f, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		move(180, 0.05f, deltaTime);
}
