#pragma once
#include <SFML\Graphics.hpp>
#include <Windows.h>
#include <string>
#include "Ability.h"

class Level
{
public:
	Level(int exp);
	void getExp(int exp);
	void addExp(int add);
	void levelUp(int level);
	int printStHigh();
	int printStLow();
	int printLvl();
	int printExp();
	int printExpToLv();
	
private:
	int level;
	int exp;
	int expLvl;
	int stHigh = 2;
	int stLow = 0;

};
