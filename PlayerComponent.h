#pragma once
#include "Component.h"
#include <glm/glm.hpp>
#include <ctime>
#include <memory>
#include <list>

struct GLFWwindow;
class GameObject;

class PlayerComponent : public Component {
public:
	PlayerComponent(GLFWwindow* window, float speed = 15);
	~PlayerComponent();

	void update(float deltaTime) override;

	bool checkCollision(std::list<std::shared_ptr<GameObject>>& objects);

	bool bIsRunning;
	bool bMoving;
	bool bForcedStopRunning;
	bool bPlayOutOfBreathSound;

private:
	GLFWwindow* window;
	GameObject* obj;
	const float speed;

	bool bShiftPressed = false;
	bool bWPressed = false;
	bool bRecovering = false;

	clock_t timeStarted = 0;
	clock_t recoverTime = 0;

	glm::vec3 tempPosition = glm::vec3(0, 0, 0);
	glm::vec3 oldPosition = glm::vec3(0, 0, 0);
private:
	void move(float angle, float fac, float deltaTime);
	void playerInput(float deltaTime);
	void checkMaxRunTime();
};