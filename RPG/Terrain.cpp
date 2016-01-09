#include "Terrain.h"

Grass::Grass(){
	picture.loadFromFile("grass.png");
	pictureSprite.setTexture(picture);
}

sf::Sprite &Grass::printTerrain(){
	return this->pictureSprite;
}


Hill::Hill(){
	picture.loadFromFile("hill.png");
	pictureSprite.setTexture(picture);
}

sf::Sprite &Hill::printTerrain(){
	return this->pictureSprite;
}
