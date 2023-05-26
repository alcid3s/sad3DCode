#pragma once
#include <glm/gtc/matrix_transform.hpp>
#include <list>
#include <vector>
#include <memory>

class GameObject;
class Texture;
class ObjModel;

class CubeComponent;
class PlaneComponent;


class MazeGenerator {
public:
	MazeGenerator();
	~MazeGenerator();

	std::vector<std::vector<std::shared_ptr<GameObject>>> Generate(const int& sizeOfMazeX = 10, const int& sizeOfMazeZ = 10);

	// place where enemy will spawn.
	GameObject* enemySpawnTile;

	// tile where player will begin
	GameObject* spawnTile;
	glm::vec3 spawnPoint = glm::vec3(0, 0, 0);

	// place where altar will stand
	GameObject* endTile;
	glm::vec3 endPoint = glm::vec3(2, 0, 2);

private:
	int x, y;
	int amountOfTiles = 0;
	std::vector<Texture*> mazeTextures;
	std::vector<std::vector<std::shared_ptr<GameObject>>> maze;

	ObjModel* altar;

	// functions to setup the maze
private:
	bool IsEdge(const int& x, const int& z, const int& sizeX, const int& sizeZ);
	bool NextToEdge(const int& x, const int& z, const int& sizeX, const int& sizeZ);

	void SetupMaze(const int& sizeOfMazeX, const int& sizeOfMazeZ);

	glm::vec3 SetSpawnPoint(const int& sizeX, const int& sizeZ);
	void SetEnemySpawnPoint(const int& sizeX, const int& sizeZ);
	CubeComponent* PlaceEmptyGameobject(const int& x, const int& z);
	CubeComponent* PlaceWall(const float& x, const float& z);
	PlaneComponent* PlaceFloor(const float& x, const float& z);
	ObjModel* PlaceAltar();

	// functions to walk the maze and apply DFS algorithm
private:
	void DepthFirstSearch(GameObject* tile, std::list<GameObject*>* visitedTiles);
	void FillMaze(const int& sizeX, const int& sizeZ);
};

// out of class because they're needed in FpsCam too.
std::list<GameObject*> GetUnvisitedNeighbours(GameObject* gameObject);
std::list<GameObject*> GetNeighbours(GameObject* gameObject);
bool NextToFloor(GameObject* gameObject);