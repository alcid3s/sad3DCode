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

std::vector<std::vector<std::shared_ptr<GameObject>>> MazeGenerator::Generate(const int& sizeOfMazeX, const int& sizeOfMazeZ)
{
	if (sizeOfMazeX < 5 || sizeOfMazeZ < 5) {
		std::cout << "maze must be atleast 5 wide and 5 long.\n";
		exit(1);
	}

	srand(time(NULL));

	// setup maze to traverse.
	SetupMaze(sizeOfMazeX, sizeOfMazeZ);
	// getting the starting tile.
	spawnTile = maze.at((int)spawnPoint.z * -1).at((int)spawnPoint.x * -1).get();
	spawnTile->addComponent(std::make_shared<PlaneComponent>(glm::vec3(1, 0, 1), mazeTextures[0]));
	std::list<GameObject*> visitedTiles;

	return this->maze;
}

void MazeGenerator::SetupMaze(const int& sizeOfMazeX, const int& sizeOfMazeZ)
{
	this->spawnPoint = SetSpawnPoint(sizeOfMazeX, sizeOfMazeZ);
	std::cout << "Spawnpoint: (" << -spawnPoint.x << "," << -spawnPoint.z << ")\n";


	// set an empty maze with walls to work with.
	for (int z = 0; z <= sizeOfMazeZ; z++) {
		std::vector<std::shared_ptr<GameObject>> file;
		for (int x = 0; x <= sizeOfMazeX; x++) {

			// position gets a GameObject.
			auto obj = std::make_shared<GameObject>();

			// check if it's an edge. If so, place Wall.
			if (IsEdge(x, z, sizeOfMazeX, sizeOfMazeZ)) {
				obj->position = glm::vec3(x, 0.f, z);
				obj->addComponent(std::make_shared<CubeComponent>(glm::vec3(1, 1, 1), mazeTextures[1]));
			}

			// not an edge
			else {
				this->amountOfTiles++;
				obj->position = glm::vec3(x, 0, z);
				obj->addComponent(std::make_shared<PlaneComponent>(glm::vec3(1, 0.01, 1), mazeTextures[0]));

			}
			file.push_back(obj);
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