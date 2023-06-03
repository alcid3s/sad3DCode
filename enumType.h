#pragma once
#include "GameObject.h"
#include <memory>
enum Type {
	Floor = 0,
	Wall = 1,
	Edge = 2,
	Empty = 3,
	Endpoint = 4,
	Spawnpoint = 5,
	Player = 6,
	Enemy = 7,
	TypeNone = -1
};

struct Cell {
	GameObject gameObject;
	bool visited;
};
