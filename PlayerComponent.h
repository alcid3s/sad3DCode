#pragma once
#include "Component.h"
#include <ctime>

struct GLFWwindow;
class GameObject;

class PlayerComponent : public Component {
public:
	PlayerComponent(GLFWwindow* window, float speed =15);
	~PlayerComponent();

	void update(float deltaTime) override;

	bool bIsRunning;
	bool bMoving;
	bool bForcedStopRunning;

private:
	GLFWwindow* window;
	GameObject* obj;
	float speed;

	bool bShiftPressed = false;
	bool bWPressed = false;
	bool bRecovering = false;

	clock_t timeStarted = 0;
	clock_t recoverTime = 0;
private:
	void move(float angle, float fac, float deltaTime);
	void playerInput(float deltaTime);
	void checkMaxRunTime();
};