#pragma once
#include "DetectMemoryLeaks.h"
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
	static DistanceWeapon Bow;
	static DistanceWeapon Crossbow;
	static DistanceWeapon Longbow;
	static DistanceWeapon Slingshot;
	static Shield LightShield;
	static Shield HeavyShield;
	static Armour Gambeson;
	static Armour LeatherArmor;
	static Armour MailShirt;
	static Armour Chainmail;
	static Armour PlateArmor;
};



//