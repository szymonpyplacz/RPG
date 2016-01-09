#include "Terrain.h"
#include <vector>
#include <utility>
#pragma once

class Map
{
public:
	Map();
	void addPosition(std::pair<int, int>);
	void freePosition(std::pair<int, int>);
	bool isEmpty(std::pair<int, int>);

private:
	std::vector<std::pair<int, int>> busyPosition;
};
