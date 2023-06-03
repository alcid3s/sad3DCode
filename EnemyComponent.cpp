#include "EnemyComponent.h"
#include "GameObject.h"
#include "enumType.h"
#include "ObjModel.h"

EnemyComponent::EnemyComponent(std::list<std::shared_ptr<GameObject>>& objects, std::string path) : objects(objects)
{
	for (auto& obj : objects) {
		if (obj->type == Type::Floor) {
			amountOfFloors++;
		}
	}
	model = new ObjModel(path);
}

EnemyComponent::~EnemyComponent()
{

}

void EnemyComponent::update(float deltaTime)
{
	if (!bMoving && !bIdle) {
		this->target = generateNewTarget();
		bMoving = true;
	}

	if (bMoving && this->target.x != -1.f && this->target.z != -1.f) {
		moveTo();
	}
}

void EnemyComponent::draw()
{
	if (model) {
		model->draw();
	}
}

/*
	Function generates a random position that it has to move towards.
*/
glm::vec3 EnemyComponent::generateNewTarget() {
	glm::vec3 target = glm::vec3(-1, -1, -1);
	int randomPosition = rand() % amountOfFloors;
	for (auto& obj : objects) {
		if (obj->type == Floor) {
			if (randomPosition == 0)
				target = obj->position;
			else
				randomPosition--;
		}
	}
	return target;
}

/*
	Takes shortest path to position
*/
void EnemyComponent::moveTo() {

}