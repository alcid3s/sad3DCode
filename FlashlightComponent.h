#pragma once
#include "DrawComponent.h"
#include <glm/gtc/matrix_transform.hpp>
#include <string>

class ObjModel;

class FlashlightComponent : public DrawComponent {
public:
	FlashlightComponent(std::string path = "resource/models/flashlight/flashlight.obj");
	~FlashlightComponent();

	void update(float deltaTime) override;
	void draw() override;

public:
	bool bIsRunning;
private:
	glm::mat4 mat;
	ObjModel* obj;
private:
	void drawLight();
	void updateFlashlight();
};