#pragma once
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
	bool walkable = 1;
	sf::Texture picture;
	sf::Sprite pictureSprite;
};