#include "CollisionComponent.h"
#include "CubeComponent.h"
CollisionComponent::CollisionComponent()
{
}

CollisionComponent::~CollisionComponent()
{
}

bool CollisionComponent::isColliding(std::shared_ptr<BoundingBoxComponent> obj) {
       return (obj->collide(gameObject->getSharedPtr()));   
}

void CollisionComponent::update(float deltaTime)
{
}
