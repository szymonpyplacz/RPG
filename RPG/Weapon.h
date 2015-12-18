#pragma once
#include <SFML\Graphics.hpp>
#include <cstring>
#include <Windows.h>
#include <iostream>
#include <cstring>
#include "Dice.h"

class Weapon
{
public:
	enum listOfWeapons
	{
		Fist = 0,
		Dagger,
		ShortSword,
		SmallAxe,
		Longsword,
		Spear,
		TwoHandedSword,
		TwoHandedAxe,
	};
	Weapon();
	Weapon(int dmg, bool soldier, bool twoHanded, bool light, int critic, int criticRange, listOfWeapons numb);
	sf::String printWeapon();
	int printWeaponDmg();
	int printCr();
	std::string printCrRg();
	sf::Sprite printSprite();

private:
	sf::Sprite pictureSprite;
	sf::Texture picture;
	sf::String name;
	Dice Damage;
	bool soldier;
	bool twoHanded;
	bool light;
	int critic;
	int criticRange;
	listOfWeapons WeaponList;
};

//class DistanceWeapon : public Weapon
//{
//public:
//	DistanceWeapon : public Weapon();
//	~DistanceWeapon : public Weapon();
//
//private:
//
//};

