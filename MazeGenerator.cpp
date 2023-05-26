#include "MazeGenerator.h"
#include "Texture.h"
#include "ObjModel.h"
#include "GameObject.h"
#include "PlaneComponent.h"
#include "CubeComponent.h"

#include <iostream>

MazeGenerator::MazeGenerator() {
	// added pointer of Texture to the vector.
	mazeTextures.push_back(new Texture("resource/textures/Floor4.png"));
	mazeTextures.push_back(new Texture("resource/textures/Bush_Texture4.png"));

	altar = new ObjModel("resource/models/altar/Altar.obj");
}

MazeGenerator::~MazeGenerator()
{
}

std::vector<std::vector<std::shared_ptr<Cell>>> MazeGenerator::Generate(const int& sizeOfMazeX, const int& sizeOfMazeZ)
{
	if (sizeOfMazeX < 5 || sizeOfMazeZ < 5) {
		std::cout << "maze must be atleast 5 wide and 5 long.\n";
		exit(1);
	}

	srand(time(NULL));

	// setup maze to traverse.
	SetupMaze(sizeOfMazeX, sizeOfMazeZ);

	// getting the starting tile.
	spawnGameObject = maze.at((int)spawnPoint.z * -1).at((int)spawnPoint.x * -1)->gameObject;
	spawnGameObject->addComponent(std::make_shared<PlaneComponent>(glm::vec3(1, 0, 1), mazeTextures[0]));
	std::vector<std::shared_ptr<Cell>> visitedTiles;

	auto cell = std::make_shared<Cell>(spawnGameObject, true, Type::Floor);

	// create maze with DFS algorithm
	DepthFirstSearch(cell, &visitedTiles);

	return this->maze;
}

void MazeGenerator::DepthFirstSearch(std::shared_ptr<Cell> tile, std::vector<std::shared_ptr<Cell>>* visitedTiles) {
	tile->visited = true;

	std::vector<std::shared_ptr<Cell>> neighbours = GetUnvisitedNeighbours(tile, &maze);

	while (!neighbours.empty()) {
		int random = rand() % neighbours.size();

		// Get random unvisited tile.
		auto nextTile = neighbours[random];

		// set the unvisited tile to a plane.
		nextTile->gameObject->addComponent(std::make_shared<PlaneComponent>(glm::vec3(1, 0, 1), mazeTextures[0]));
		nextTile->type = Type::Floor;

		visitedTiles->push_back(tile);

		DepthFirstSearch(nextTile, visitedTiles);

		neighbours = GetUnvisitedNeighbours(tile, &maze);
	}

	if (visitedTiles->size() == amountOfTiles)
		return;

	std::shared_ptr<Cell> backtrackTile = nullptr;
	for (int i = visitedTiles->size() - 1; i >= 0; i--) {
		auto tile = visitedTiles->at(i);
		std::vector<std::shared_ptr<Cell>> neighbors = GetUnvisitedNeighbours(tile, &maze);

		if (!neighbors.empty()) {
			backtrackTile = tile;
			break;
		}
	}

	if (backtrackTile) {
		DepthFirstSearch(backtrackTile, visitedTiles);
	}
}

std::vector<std::shared_ptr<Cell>> GetNeighbours(std::shared_ptr<Cell> tile, std::vector<std::vector<std::shared_ptr<Cell>>> maze) {
	std::vector<std::shared_ptr<Cell>> neighbours;
	auto neighbour = std::shared_ptr<Cell>();

	// get north neighbour
	neighbour = maze[tile->gameObject->position.z - 1][tile->gameObject->position.x];
	if (neighbour) {
		neighbours.push_back(neighbour);
	}

	// get east neighbour
	neighbour = maze[tile->gameObject->position.z][tile->gameObject->position.x + 1];
	if (neighbour) {
		neighbours.push_back(neighbour);
	}

	// get south neighbour
	neighbour = maze[tile->gameObject->position.z + 1][tile->gameObject->position.x];
	if (neighbour) {
		neighbours.push_back(neighbour);
	}

	// get west neighbour
	neighbour = maze[tile->gameObject->position.z][tile->gameObject->position.x - 1];
	if (neighbour) {
		neighbours.push_back(neighbour);
	}

	return neighbours;
}

std::vector<std::shared_ptr<Cell>> GetUnvisitedNeighbours(std::shared_ptr<Cell> currentTile, std::vector<std::vector<std::shared_ptr<Cell>>>* maze) {
	std::vector<std::shared_ptr<Cell>> neighbours = GetNeighbours(currentTile, *maze);

	std::vector<std::shared_ptr<Cell>> tilesToRemove;
	for (auto& tile : neighbours) {
		if (tile->visited || NextToFloor(tile))
			tilesToRemove.push_back(tile);
	}
	neighbours.erase(std::remove_if(neighbours.begin(), neighbours.end(), [&tilesToRemove](std::shared_ptr<Cell> tile) {
		return std::find(tilesToRemove.begin(), tilesToRemove.end(), tile) != tilesToRemove.end();
		}), neighbours.end());

	return neighbours;
}

void MazeGenerator::SetupMaze(const int& sizeOfMazeX, const int& sizeOfMazeZ)
{
	this->spawnPoint = SetSpawnPoint(sizeOfMazeX, sizeOfMazeZ);
	std::cout << "Spawnpoint: (" << -spawnPoint.x << "," << -spawnPoint.z << ")\n";


	// set an empty maze with walls to work with.
	for (int z = 0; z <= sizeOfMazeZ; z++) {
		std::vector<std::shared_ptr<Cell>> file;
		for (int x = 0; x <= sizeOfMazeX; x++) {

			// position gets a GameObject.
			auto cell = std::make_shared<Cell>(new GameObject(), false, Type::TypeNone);

			// check if it's an edge. If so, place Wall.
			if (IsEdge(x, z, sizeOfMazeX, sizeOfMazeZ)) {
				cell->gameObject->position = glm::vec3(x, 0.f, z);
				cell->gameObject->addComponent(std::make_shared<CubeComponent>(glm::vec3(1, 1, 1), mazeTextures[1]));
			}

			// not an edge
			else {
				this->amountOfTiles++;
				cell->gameObject->position = glm::vec3(x, -.5f, z);

			}
			file.push_back(cell);
		}
		maze.push_back(file);
	}
}

glm::vec3 MazeGenerator::SetSpawnPoint(const int& sizeX, const int& sizeZ) {
	std::vector<glm::vec3> possibleSpawnPoints;
	for (int x = 0; x <= sizeX; x++) {
		for (int z = 0; z <= sizeZ; z++) {
			if (NextToEdge(x, z, sizeX, sizeZ)) {
				possibleSpawnPoints.push_back(glm::vec3((float)x, 0.f, (float)z));
			}
		}
	}
	int num = rand() % possibleSpawnPoints.size();
	glm::vec3 sPoint = -possibleSpawnPoints.at(num);
	return sPoint;
}

bool MazeGenerator::IsEdge(const int& x, const int& z, const int& sizeX, const int& sizeZ) {
	return (x == sizeX || x == 0 || z == 0 || z == sizeZ);
}

bool MazeGenerator::NextToEdge(const int& x, const int& z, const int& sizeX, const int& sizeZ) {
	// if on north or south edge of maze.
	if (z == (sizeZ - 1) || z == 1) {
		if (x > 0 && x < sizeX) {
			return true;
		}
	}
	// if at east or west edge.
	else if (x == (sizeX - 1) || x == 1) {
		if (z > 0 && z < sizeZ) {
			return true;
		}
	}
	return false;
}

bool NextToFloor(std::shared_ptr<Cell> currentTile, std::vector<std::vector<std::shared_ptr<Cell>>> maze) {
	int connections = 0;
	std::vector<std::shared_ptr<Cell>> neighbours = GetNeighbours(currentTile, maze);
	for (auto& tile : neighbours) {
		if (tile->type == Type::Floor) {
			connections++;
		}
	}
	return connections > 1;
}