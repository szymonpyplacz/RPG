#include "Terrain.h"

Grass::Grass(){
	picture.loadFromFile("grass.png");
	pictureSprite.setTexture(picture);
}

sf::Sprite &Grass::printTerrain(){
	return this->pictureSprite;
}
