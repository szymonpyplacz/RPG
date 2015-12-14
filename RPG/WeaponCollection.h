#pragma once
#include <SFML\Graphics.hpp>
#include <cstring>
#include <Windows.h>
#include <iostream>
#include <cstring>
#include "Weapon.h"
#include "Dice.h"

//int dmg, bool soldier, bool twoHanded, bool light, int crit, int crRange, 

class WeaponCollection
{
public:
	static Weapon Fist;
	static Weapon Dagger;
	static Weapon ShortSword;
	static Weapon SmallAxe;
	static Weapon Longsword;
	static Weapon Spear;
	static Weapon TwoHandedSword;
	static Weapon TwoHandedAxe;
};


//