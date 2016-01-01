#pragma once
#include <SFML\Graphics.hpp>
#include <Windows.h>
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

private:
	sf::Sprite pictureSprite;
	sf::Texture picture;
	int hp;
	int hpMax;


};
