#include "CollisionComponent.h"
#include "CubeComponent.h"
CollisionComponent::CollisionComponent()
{
}

CollisionComponent::~CollisionComponent()
{
}

bool CollisionComponent::isColliding(std::shared_ptr<BoundingBoxComponent> player) {
        return (player->collide(std::make_shared<GameObject>(gameObject)));   
}