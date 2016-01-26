#pragma once
#include "DetectMemoryLeaks.h"
#include <SFML\Graphics.hpp>
#include <cstring>
#include <Windows.h>
#include <iostream>
#include <cstring>


class Terrain
{
public:
	virtual sf::Sprite& printTerrain() = 0;
	virtual ~Terrain(){};
private:
};

class Grass :public Terrain{
public:
	Grass();
	sf::Sprite& printTerrain();
private:
	sf::Texture picture;
	sf::Sprite pictureSprite;
};

class Hill :public Terrain{
public:
	Hill();
	sf::Sprite& printTerrain();
private:
	sf::Texture picture;
	sf::Sprite pictureSprite;
};