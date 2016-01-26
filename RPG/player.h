#pragma once
#include "DetectMemoryLeaks.h"
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
#include "Map.h"


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
	sf::Sprite& printAvatar();
	sf::Sprite& printIcon();
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
	void setShield(Shield shield);
	void setArmour(Armour arm);
	void changeWeapon();
	int printAC();
	int printBasicAttack();
	int printSpeed();
	int printDistanceAttack();
	int setSpeed();
	void setLeftMove();
	int printLeftMove();
	bool isMeleeWeapon();
	bool wasCrossedMove();
	void setCrossedMove();
	void isCrossedMove();
	void setPosition(int x, int y, Map& mapa);
	void endTurn();
	pair<int, int> getPosition();
	Shield getShield();
	Weapon getMainWeapon();
	DistanceWeapon getSecondWeapon();
	Armour getArmour();
	Hp& getHp();
	Level& getLevel();
	Player(playerClass plCl, rase plRase, Ability str, Ability dex, Ability con, Ability itl, Ability wis, Ability cha, Level lvl, Armor ac, bool male, string name);
	Player();
	///dodawane teraz
	void moveLeft(Map&mapa, Text& text);
	void moveLeftTop(Map&mapa, Text& text);
	void moveLeftDown(Map&mapa, Text& text);
	void moveRight(Map&mapa, Text& text);
	void moveRightTop(Map&mapa, Text& text);
	void moveRightDown(Map&mapa, Text& text);
	void moveTop(Map&mapa, Text& text);
	void moveDown(Map&mapa, Text& text);

private:
	pair<int, int> position;
	playerClass PlayerCl;
	rase PlayerRase;
	string name;
	Hp hp;
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
	int leftMove = 0;
	bool wasCrossMove = 0;
	bool isCrossMove = 0;
	int basicAttack = 0;
	int init = 0;
	bool male;
	bool isUsingMeleeWeapon;
	sf::Sprite avatarSprite;
	sf::Sprite iconSprite;
	sf::Texture avatar;
	sf::Texture icon;
	Weapon mainWeapon;
	DistanceWeapon secondWeapon;
	Shield playerShield;
	Armour playerArmour;
};


class NPC : public Player{
public:
	string printName();
	sf::Sprite& printIcon();
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
	int returnExpValue();
	void modAtrFromRase();
	void setMainWeapon(Weapon weap);
	void setDistanceWeapon(DistanceWeapon weap);
	void setShield(Shield shield);
	void setArmour(Armour arm);
	void changeWeapon();
	int printAC();
	int printBasicAttack();
	int printSpeed();
	int printDistanceAttack();
	int setSpeed();
	void setLeftMove();
	int printLeftMove();
	bool isMeleeWeapon();
	bool wasCrossedMove();
	void setCrossedMove();
	void isCrossedMove();
	void setPosition(int x, int y, Map& mapa);
	void endTurn();
	pair<int, int> getPosition();
	Shield getShield();
	Weapon getMainWeapon();
	DistanceWeapon getSecondWeapon();
	Armour getArmour();
	Hp& getHp();
	NPC(bool archer, Ability str, Ability dex, Ability con, Ability itl, Ability wis, Ability cha, Level lvl, Armor ac);
	NPC();

private:
	int expValue;
	pair<int, int> position;
	playerClass PlayerCl;
	rase PlayerRase;
	Hp hp;
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
	int leftMove = 0;
	bool wasCrossMove = 0;
	bool isCrossMove = 0;
	int basicAttack = 0;
	int init = 0;
	bool male;
	bool isUsingMeleeWeapon;
	sf::Sprite avatarSprite;
	sf::Sprite iconSprite;
	sf::Texture avatar;
	sf::Texture icon;
	Weapon mainWeapon;
	DistanceWeapon secondWeapon;
	Shield playerShield;
	Armour playerArmour;
};