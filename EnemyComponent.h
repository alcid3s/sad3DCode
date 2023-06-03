#pragma once
#include "DrawComponent.h"
#include "glm/glm.hpp"
#include <list>
#include <memory>
#include <string>

class GameObject;
class ObjModel;

class EnemyComponent : public DrawComponent {
public:
	EnemyComponent(std::list<std::shared_ptr<GameObject>>& objects, std::string path = "resource/models/enemy/enemy.obj");
	~EnemyComponent();

	void update(float deltaTime) override;
	void draw() override;

protected:
	bool bMoving = false;
	bool bIdle = false;

	glm::vec3 target = glm::vec3(-1, -1, -1);

	size_t amountOfFloors = 0;

	std::list<std::shared_ptr<GameObject>>& objects;

	ObjModel* model;
protected:
	glm::vec3 generateNewTarget();
	void moveTo();
};