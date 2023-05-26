#pragma once
#include "Component.h"
#include <glm/gtc/matrix_transform.hpp>

struct GLFWwindow;

class CameraComponent : public Component {
public:
	CameraComponent(GLFWwindow* window);
	~CameraComponent();

	glm::mat4 getMatrix();
	void update(float deltaTime) override;
protected:
	GLFWwindow* window;
};