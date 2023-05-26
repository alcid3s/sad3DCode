#pragma once
#include "GameObject.h"
#include <memory>
enum Type {
	Floor = 0,
	Wall = 1,
	Edge = 2,
	Empty = 3,
	Endpoint = 4,
	TypeNone = -1
};

struct Cell {
	std::shared_ptr<GameObject> gameObject;
	bool visited;
	Type type;
};
