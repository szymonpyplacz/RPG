#pragma once
#include <SFML\Graphics.hpp>
#include <Windows.h>
#include <string>
#include <random>

#ifndef _DICE_H
#define _DICE_H

class Dice
{
public:
	Dice();
	Dice(int size);
	int rollDice();
	int returnSize();

private:
	int size;
};

#endif