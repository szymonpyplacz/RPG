#pragma once
#include "DetectMemoryLeaks.h"
#include "Terrain.h"
#include <vector>
#include <utility>



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
