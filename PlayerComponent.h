#pragma once
#include "Component.h"

struct GLFWwindow;
class GameObject;

class PlayerComponent : public Component {
public:
	PlayerComponent(GLFWwindow* window, float speed = 50);
	~PlayerComponent();

	virtual void update(float deltaTime) override;

	bool bIsRunning;

private:
	GLFWwindow* window;
	GameObject* obj;
	float speed;

	bool bShiftPressed = false;
	bool bWPressed = false;
private:
	void move(float angle, float fac, float deltaTime);
	void playerInput(float deltaTime);
	void changeFOV(float deltaTime);
};