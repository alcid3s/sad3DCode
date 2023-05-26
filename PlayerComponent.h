#pragma once
#include "Component.h"

struct GLFWwindow;
class GameObject;

class PlayerComponent : public Component {
public:
	PlayerComponent(GLFWwindow* window, float speed = 450);
	~PlayerComponent();

	void move(float angle, float fac, float deltaTime);
	virtual void update(float deltaTime) override;
private:
	GLFWwindow* window;
	GameObject* obj;
	float speed;
};