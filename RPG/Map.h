#include "Terrain.h"

class Map
{
public:
	Map();
	sf::Sprite& printMap();
	void print();
	void setMap();

private:
	std::vector<Grass> wektor;
};
