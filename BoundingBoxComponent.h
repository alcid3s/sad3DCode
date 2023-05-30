#pragma once
#include "Component.h"
#include <glm/glm.hpp>
#include "GameObject.h"
#include <memory>
class BoundingBoxComponent : public Component {
public:
	BoundingBoxComponent();
	~BoundingBoxComponent();

	void update(float deltaTime) override;
	bool collide(std::shared_ptr<GameObject> player);

	glm::vec3 min;
	glm::vec3 max;
	glm::vec3 lengths;
};