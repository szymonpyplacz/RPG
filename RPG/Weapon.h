#pragma once
#include <SFML\Graphics.hpp>
#include <cstring>
#include <Windows.h>
#include <iostream>
#include <cstring>
#include "Dice.h"

enum class listOfWeapons{ Fist, Dagger, ShortSword, SmallAxe, Longsword, Spear, TwoHandedSword, TwoHandedAxe };
enum class listOfDistanceWeapons{Bow, Crossbow, Longbow, Slingshot};
enum class listOfShields{ LightShield, HeavyShield };
enum class listOfArmour {Gambeson, LeatherArmor, MailShirt, Chainmail, PlateArmor};
class Weapon
{
public:
	Weapon();
	Weapon(int dmg, bool soldier, bool twoHanded, bool light, int critic, int criticRange, listOfWeapons numb);
	sf::String printWeapon();
	int printWeaponDmg();
	int printCr();
	bool isTwoHanded();
	bool isSoldier();
	std::string printCrRg();
	int printCrRange();
	sf::Sprite printSprite();
	Dice returnDice();

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

class DistanceWeapon : public Weapon
{
public:
	sf::String printWeapon();
	int printWeaponDmg();
	int printCr();
	std::string printCrRg();
	sf::Sprite printSprite();
	int printCrRange();
	int printMissles();
	int printRange();
	DistanceWeapon();
	DistanceWeapon(int dmg, bool soldier,  int critic, int criticRange, int range, int missles, listOfDistanceWeapons numb);
private:
	int range;
	int missles;
	sf::Sprite pictureSprite;
	sf::Texture picture;
	sf::String name;
	Dice Damage;
	bool soldier;
	bool twoHanded;
	int critic;
	int criticRange;
	listOfDistanceWeapons WeaponList;
};

class Shield
{
public:
	Shield();
	Shield(int ac, listOfShields numb);
	sf::String printShield();
	sf::Sprite printSprite();
	int getAC();
private:
	int ac;
	sf::Sprite pictureSprite;
	sf::Texture picture;
	sf::String name;
	listOfShields ShieldList;
};

class Armour
{
public:
	Armour();
	Armour(int ac, int speed, int maxDex, bool heavy, listOfArmour numb);
	sf::String printArmour();
	sf::Sprite printSprite();
	int getAC();
	bool isHeavy();
	int printMaxDex();
	int printSpeed();
private:
	int ac;
	int speed;
	int maxDex;
	bool heavy;
	sf::Sprite pictureSprite;
	sf::Texture picture;
	sf::String name;
	listOfArmour ArmourList;
};
