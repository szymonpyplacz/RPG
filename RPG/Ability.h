#pragma once
#include "DetectMemoryLeaks.h"
#include <SFML\Graphics.hpp>
#include <Windows.h>
#include <string>


class Ability
{
public:
	int printAb();
	int printMod();
	void setValue(int value);
	Ability(int value);
	Ability();

private:
	int value;
	int mod;

};


