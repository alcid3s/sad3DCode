#pragma once
#include "Component.h"
#include "BoundingBoxComponent.h"
#include <memory>

class CollisionComponent : public Component {
public:
	CollisionComponent();
	~CollisionComponent();
	bool isColliding(std::shared_ptr<BoundingBoxComponent> player);

	void update(float deltaTime) override;
};