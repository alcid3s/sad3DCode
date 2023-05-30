#include "BoundingBoxComponent.h"

BoundingBoxComponent::BoundingBoxComponent()
{
}

BoundingBoxComponent::~BoundingBoxComponent()
{
}

bool BoundingBoxComponent::collide(std::shared_ptr<GameObject> player)
{
	return false;
}

void BoundingBoxComponent::update(float deltaTime)
{
}