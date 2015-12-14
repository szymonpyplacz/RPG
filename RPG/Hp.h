#pragma once
#include <SFML\Graphics.hpp>
#include <Windows.h>
#include <string>
#include "Ability.h"

class Hp
{
public:
	Hp(int maxHP);
	void getHp(int newHp);
	void getHpMax(int newHpMax);
	void getDmg(int dmg);

	int printHP();
	int printMaxHP();
	
private:
	bool alive;
	int hp;
	int hpMax;


};
