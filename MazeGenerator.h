#pragma once
#include <glm/gtc/matrix_transform.hpp>
#include <list>
#include <vector>
#include <memory>
#include "enumType.h"

class GameObject;
class Texture;
class ObjModel;

class CubeComponent;
class PlaneComponent;

class MazeGenerator {
public:
	MazeGenerator();
	~MazeGenerator();

	std::vector<std::vector<std::shared_ptr<Cell>>> Generate(const int& sizeOfMazeX = 10, const int& sizeOfMazeZ = 10);

	// place where enemy will spawn.
	std::shared_ptr<GameObject> enemySpawnTile;

	// tile where player will begin
	std::shared_ptr<Cell> spawnGameObject;
	glm::vec3 spawnPoint = glm::vec3(0, 0, 0);

	// place where altar will stand
	std::shared_ptr<Cell> endTile;
	glm::vec3 endPoint = glm::vec3(2, 0, 2);

private:
	int x, y;
	int amountOfFloors = 0;
	std::vector<Texture*> mazeTextures;
	std::vector<std::vector<std::shared_ptr<Cell>>> maze;

	ObjModel* altar;

	// functions to setup the maze
private:
	bool IsEdge(const int& x, const int& z, const int& sizeX, const int& sizeZ);
	bool NextToEdge(const int& x, const int& z, const int& sizeX, const int& sizeZ);

	void SetupMaze(const int& sizeOfMazeX, const int& sizeOfMazeZ);

	glm::vec3 SetSpawnPoint(const int& sizeX, const int& sizeZ);
	void SetEnemySpawnPoint(const int& sizeX, const int& sizeZ);
	void setEndTile(const int& sizeX, const int& sizeZ);

	// functions to walk the maze and apply DFS algorithm
private:
	void DepthFirstSearch(std::shared_ptr<Cell> tile, std::vector<std::shared_ptr<Cell>>* visitedTiles);
	void FillMaze(const int& sizeX, const int& sizeZ);
};

std::vector<std::shared_ptr<Cell>> GetUnvisitedNeighbours(std::shared_ptr<Cell> tile, std::vector<std::vector<std::shared_ptr<Cell>>>& maze);
std::vector<std::shared_ptr<Cell>> GetNeighbours(std::shared_ptr<Cell> tile, std::vector<std::vector<std::shared_ptr<Cell>>>& maze);
bool NextToFloor(std::shared_ptr<Cell> currentTile, std::vector<std::vector<std::shared_ptr<Cell>>> maze);