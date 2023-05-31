#include "PlayerComponent.h"
#include "GameObject.h"
#include "BoundingBoxComponent.h"
#include <GLFW/glfw3.h>
#include <ctime>
#include <iostream>

#define maxRunningTime 4
#define maxRecoverTime 4

PlayerComponent::PlayerComponent(GLFWwindow* window, float speed)
	: window(window), speed(speed), bForcedStopRunning(false), bIsRunning(false), bMoving(false), obj(nullptr)
{

}

PlayerComponent::~PlayerComponent()
{

}


void PlayerComponent::move(float angle, float fac, float deltaTime)
{
	this->bMoving = true;

	this->tempPosition.x += (float)cos(gameObject->rotation.y + glm::radians(angle)) * fac * speed * deltaTime;
	this->tempPosition.z += (float)sin(gameObject->rotation.y + glm::radians(angle)) * fac * speed * deltaTime;
}

void PlayerComponent::update(float deltaTime)
{
	playerInput(deltaTime);
	checkMaxRunTime();
}

bool PlayerComponent::checkCollision(std::list<std::shared_ptr<GameObject>>& objects) {
	bool collides = false;
	if (this->tempPosition == glm::vec3(0.0f, 0.0f, 0.0f)) {
		return collides;
	}
	this->tempPosition = gameObject->position + this->tempPosition;
	this->oldPosition = gameObject->position;

	gameObject->position = this->tempPosition;
	if (!gameObject->getComponent<BoundingBoxComponent>()) {
		return false;
	}
	for (auto& obj : objects) {
		if (gameObject->getComponent<BoundingBoxComponent>()->collide(obj)) {
			collides = true;
			// std::cout << "colliding with: (" << obj->position.x << "," << obj->position.y << "," << obj->position.z << "), position of player is: (" << tempPosition.x << "," << tempPosition.y << "," << tempPosition.z << ")\n";;
			break;
		}
	}

	if (collides) {
		gameObject->position = this->oldPosition;
	}

	// std::cout << "player pos: (" << tempPosition.x << "," << tempPosition.y << "," <<tempPosition.z << ")\n";

	this->tempPosition = glm::vec3(0, 0, 0);

	return collides;
}

void PlayerComponent::playerInput(float deltaTime)
{
	bMoving = false;
	float multi = 1.f;
	// multiplier for running
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS && !bRecovering) {
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
	else {
		bWPressed = false;
	}
		
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
}

void PlayerComponent::checkMaxRunTime()
{
	if (bWPressed && bShiftPressed && !bIsRunning && !bRecovering) {
		timeStarted = clock();
		bIsRunning = true;
	}
	else if ((!bWPressed || !bShiftPressed) && bIsRunning) {
		bIsRunning = false;
	}

	if (clock() - timeStarted > maxRunningTime * CLOCKS_PER_SEC && bIsRunning && !bRecovering) {
		bRecovering = true;
		bIsRunning = false;
		recoverTime = clock();
	}

	if (clock() - recoverTime > maxRecoverTime * CLOCKS_PER_SEC && bRecovering) {
		bRecovering = false;
	}
}

