#pragma once
#include <SFML\Graphics.hpp>
#include <Windows.h>
#include <string>
#include "Ability.h"
#include "DetectMemoryLeaks.h"


class Armor
{
public:
	Armor();
	void getAC(int armor);
	int printAC();


private:
	int ac;
};

