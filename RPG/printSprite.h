#pragma once
#include "DetectMemoryLeaks.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "player.h"


enum class Orders2 { Left, LeftTop, LeftDown, Top, Down, RightTop, RightDown, Right, EndTurn };

class printSprite
{
public:
	printSprite(sf::Texture texture, std::pair<int, int> cords);
	printSprite(sf::Sprite photo, std::pair<int, int> cords);
	printSprite(sf::Sprite photo, std::pair<int, int> cords, Player* gracz, Orders2 metoda);
	sf::Sprite& GetSprite();
	Orders2 getOrder();

private:
	sf::Sprite button_sprite;
	bool textured;
	sf::Texture texture;
	Orders2 method;
};