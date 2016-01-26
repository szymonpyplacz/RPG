#pragma once
#include "DetectMemoryLeaks.h"
#include <SFML\Graphics.hpp>
#include <string>
#include "Ability.h"

class Hp
{
public:
	Hp(int maxHP);
	Hp();
	void getHp(int newHp);
	void getHpMax(int newHpMax);
	void getDmg(int dmg);
	int printHP();
	int printMaxHP();
	sf::Sprite& printSprite();
	sf::Texture& printTexture();

private:
	sf::Sprite pictureSprite;
	sf::Texture picture;
	int hp;
	int hpMax;


};
