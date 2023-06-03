#pragma once
#include "DrawComponent.h"
#include "glm/glm.hpp"
#include <list>
#include <vector>
#include <memory>
#include <string>

class GameObject;
class ObjModel;

class EnemyComponent : public DrawComponent {
public:
	EnemyComponent(std::list<std::shared_ptr<GameObject>>& objects, float speed = 1.f, const std::string& path = "resource/models/enemy/enemy.obj");
	~EnemyComponent();

	void update(float deltaTime) override;
	void draw() override;

protected:
	bool bMoving = false;
	bool bIdle = false;

	// speed of enemy
	float speed = 0.f;

	// position enemy should move towards
	glm::vec3 target = glm::vec3(-1, -1, -1);

	// vector of tiles to walk to get to target
	std::vector<std::shared_ptr<GameObject>> shortestPath;

	// current position in the vector of tiles to walk to target
	int posInList = 0;

	// 3d model of enemy
	ObjModel* model;
protected:
	std::vector<std::shared_ptr<GameObject>> generateNewTarget();
	void moveTo(float deltaTime);
	virtual std::vector<std::shared_ptr<GameObject>> findShortestPath(const glm::vec3& start, const glm::vec3& end);
private:
	// floors of the maze
	std::vector<std::shared_ptr<GameObject>> floors;

	// all gameobjects
	std::list<std::shared_ptr<GameObject>>& objects;

	clock_t timeToBeidle = 0;

	// distance horizontally and vertically between tiles
	const float distanceBetweenTiles = 1.25f;
private:

	// resets parameters so that a new path can be generated
	void resetParams();
};