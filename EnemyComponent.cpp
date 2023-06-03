#include "EnemyComponent.h"
#include "GameObject.h"
#include "enumType.h"
#include "ObjModel.h"

#include <unordered_map>
#include <queue>
#include <limits>
#include <iostream>

#define idleTime 5

EnemyComponent::EnemyComponent(std::list<std::shared_ptr<GameObject>>& objects, float speed, const std::string& path) : objects(objects), speed(speed)
{
	for (auto& obj : objects) {
		if (obj->type == Type::Floor) {
			floors.push_back(obj);
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
		this->shortestPath = generateNewTarget();
		posInList = 0;
		bMoving = true;
		std::cout << "enemy spawnpoint: (" << gameObject->position.x << "," << gameObject->position.z << ")\n";
	}

	if (bMoving && !bIdle) {
		moveTo(deltaTime);
	}

	if ((!bMoving && bIdle) && clock() - timeToBeidle > idleTime * CLOCKS_PER_SEC) {
		bIdle = false;
	}
}

void EnemyComponent::draw()
{
	if (model) {
		model->draw();
	}
}

void EnemyComponent::moveTo(float deltaTime) {
	if (shortestPath.empty() || shortestPath.size() == 1) {
		resetParams();
		return;
	}

	float distance = glm::distance(this->shortestPath[posInList]->position, gameObject->position);
	if (distance < speed * deltaTime) {
		gameObject->position = this->shortestPath[posInList]->position;
		if (posInList < shortestPath.size()) {
			posInList++;
			std::cout << "PosInList: " << posInList << ", size of list: " << shortestPath.size() << "\n";
		}
	}
	else {
		glm::vec3 forward = glm::normalize(gameObject->position);
		float angle = std::atan2(-forward.x, forward.z);
		gameObject->rotation.y = glm::degrees(angle);
		auto direction = glm::normalize(this->shortestPath[posInList]->position - gameObject->position);
		gameObject->position += speed * deltaTime * direction;
	}

	if (this->shortestPath[posInList]->position == target) {
		resetParams();
		bIdle = true;
		timeToBeidle = clock();
		std::cout << "reached endpoint\n";
	}
}

void EnemyComponent::resetParams() {
	this->shortestPath.clear();
	this->target = glm::vec3(-1, -1, -1);
	bMoving = false;
	bIdle = false;
}

/*
	Function generates a random position and a path to move to that target
*/
std::vector<std::shared_ptr<GameObject>> EnemyComponent::generateNewTarget() {
	glm::vec3 target = glm::vec3(-1, -1, -1);
	int randomPosition = rand() % floors.size();
	for (const auto& floor : floors) {
		if (floor->type == Floor) {
			if (randomPosition == 0) {
				target = floor->position;
				break;
			}
			else
				randomPosition--;
		}
	}
	return findShortestPath(gameObject->position, target);
}

/*
	Takes shortest path to position
*/
#include <functional>

struct Vec3Hash {
	std::size_t operator()(const glm::vec3& vec) const {
		std::size_t h1 = std::hash<float>()(vec.x);
		std::size_t h2 = std::hash<float>()(vec.y);
		std::size_t h3 = std::hash<float>()(vec.z);
		return h1 ^ (h2 << 1) ^ (h3 << 2);
	}
};

struct Vec3Equal {
	bool operator()(const glm::vec3& lhs, const glm::vec3& rhs) const {
		return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
	}
};

std::vector<std::shared_ptr<GameObject>> EnemyComponent::findShortestPath(const glm::vec3& start, const glm::vec3& end) {
	std::unordered_map<glm::vec3, bool, Vec3Hash, Vec3Equal> visited;
	std::unordered_map<glm::vec3, glm::vec3, Vec3Hash, Vec3Equal> previous;
	std::queue<glm::vec3> queue;

	// Mark the start position as visited and enqueue it
	visited[start] = true;
	queue.push(start);

	while (!queue.empty()) {
		glm::vec3 current = queue.front();
		queue.pop();

		// Check if the current position is the destination
		if (current == end) {
			// Build and return the path
			std::vector<std::shared_ptr<GameObject>> path;
			glm::vec3 pathNode = end;

			while (pathNode != start) {
				for (const auto& floor : floors) {
					if (floor->position == pathNode) {
						path.push_back(floor);
						pathNode = previous[pathNode];
						break;
					}
				}
			}

			// Reverse the path to get the correct order
			std::reverse(path.begin(), path.end());

			target = path[path.size() - 1]->position;
			return path;
		}

		// Get the direct neighbors within the specified distance
		for (const auto& floor : floors) {
			if (visited[floor->position]) {
				continue;  // Skip already visited positions
			}

			float distance = glm::distance(floor->position, current);
			if (distance <= distanceBetweenTiles) {
				visited[floor->position] = true;
				queue.push(floor->position);
				previous[floor->position] = current;
			}
		}
	}

	// No path found
	return std::vector<std::shared_ptr<GameObject>>();
}