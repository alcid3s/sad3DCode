#pragma once
#include "DrawComponent.h"
#include "tigl.h"
#include <string>

class Texture;

class HUDComponent : public DrawComponent {
	std::vector<tigl::Vertex> verts;
public:
	HUDComponent(std::string path = "resource/textures/Cam1.png");
	~HUDComponent();

	void update(float deltaTime) override;
	void draw() override;
private:
	Texture* texture;
	glm::mat4 mat;
private:
	void bindHUD();
	void unbindHUD();
};