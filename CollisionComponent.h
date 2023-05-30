#pragma once
#include "Component.h"
#include "BoundingBoxComponent.h"
#include <memory>

class CollisionComponent : public Component {
public:
	CollisionComponent();
	~CollisionComponent();
	bool isColliding(std::list<std::shared_ptr<GameObject>>& objects, std::shared_ptr<BoundingBoxComponent> player);
};