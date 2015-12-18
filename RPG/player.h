#pragma once
#include <SFML\Graphics.hpp>
#include <Windows.h>
#include <string>
#include "Ability.h"
#include "Level.h"
#include "Hp.h"
#include "Armor.h"
#include <iostream>
#include <cstring>
#include "SavingThrows.h"
#include "Weapon.h"
#include "WeaponCollection.h"

using namespace std;
using namespace sf;

enum class playerClass {fighter,hunter,priest,wizard};
enum class rase { human, elf, dwarf };

class Player
{
public:
	string printName();
	string printStr();
	string printDex();
	string printCon();
	string printInt();
	string printWis();
	string printCha();
	string printClassName();
	string printRaseName();
	sf::Sprite printAvatar();
	sf::Sprite printWeapIcon();
	
	int printSTFor();
	int printSTRef();
	int printSTWl();
	int classHP();
	void setArmor();
	void setBasicAttack();
	void setST();
	int printLvl();
	int printExp();
	int printExpToLv();
	void modAtrFromRase();
	void setMainWeapon(Weapon weap);
	void setDistanceWeapon(DistanceWeapon weap);

	int printHpMax();
	int printHpNow();
	int printAC();
	int printBasicAttack();
	int printSpeed();
	int printDistanceAttack();
	int setSpeed();


	
	Weapon getMainWeapon();
	Weapon getSecondWeapon();

	Player(playerClass plCl, rase plRase, Ability str, Ability dex, Ability con, Ability itl, Ability wis, Ability cha, Level lvl, Armor ac, bool male, char* name);

private:
	playerClass PlayerCl;
	rase PlayerRase;
	char* name;
	Hp hp = 0;
	Ability strenght;
	Ability dexterity;
	Ability constitution;
	Ability wisdom;
	Ability intelligence;
	Ability charisma;
	SavingThrow fortitude = 0;
	SavingThrow reflex = 0;
	SavingThrow will = 0;
	Level level;
	Armor ac;
	int speed = 0;
	int basicAttack = 0;
	int init = 0;
	bool male;
	sf::Sprite avatarSprite;
	sf::Texture avatar;
	Weapon mainWeapon;
	DistanceWeapon secondWeapon;

};
