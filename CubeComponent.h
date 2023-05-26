#pragma once

#include "DrawComponent.h"
#include "tigl.h"
#include <vector>

using tigl::Vertex;

class Texture;

class CubeComponent : public DrawComponent
{
	std::vector<Vertex> verts;
public:
	CubeComponent(glm::vec3 transform, Texture* texture, int textureMultiplier = 1);
	~CubeComponent();

	virtual void draw() override;

private:
	Texture* texture;
	int textureMultiplier;
};