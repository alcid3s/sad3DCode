#pragma once

enum Type {
	Floor = 0,
	Wall = 1,
	Edge = 2,
	Empty = 3,
	Endpoint = 4,
	TypeNone = -1
};

enum Bearing {
	North = 0,
	East = 1,
	South = 2,
	West = 3,
	BearingNone = -1
};
