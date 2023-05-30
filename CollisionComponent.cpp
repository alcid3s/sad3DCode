#include "CollisionComponent.h"
#include "CubeComponent.h"
CollisionComponent::CollisionComponent()
{
}

CollisionComponent::~CollisionComponent()
{
}

bool CollisionComponent::isColliding(std::list<std::shared_ptr<GameObject>>& objects, std::shared_ptr<BoundingBoxComponent> player) {
    for (const auto& object : objects) {
        if (object->getComponent<CubeComponent>()) {
            if (player->collide(object)) {
                return false;
            }
        }
    }
    return true;
}