#pragma once
#include <SFML\Graphics.hpp>
#include <Windows.h>
#include <SFML\Graphics.hpp>
#include <Windows.h>
#include <string>
#include "Ability.h"
#include "DetectMemoryLeaks.h"

class SavingThrow
{
public:
	SavingThrow(int c);
	void setVal(int a);
	int printVal();

private:
	int value;
};
