#include "player.h"
#include "Dice.h"
#include <algorithm>
#include "Weapon.h"
#include "Map.h"
#pragma once


Player::Player(){
	Player(playerClass::fighter, rase::human, Ability(0), Ability(0), Ability(0), Ability(0), Ability(0), Ability(0), Level(0), Armor(), true, "noName");
}
Player::Player(playerClass plcl, rase plRase, Ability s, Ability d, Ability c, Ability i, Ability w, Ability ch, Level lvl, Armor arcl, bool gender, string name) : PlayerCl(plcl), PlayerRase(plRase), strenght(s), dexterity(d), constitution(c), intelligence(i), wisdom(w), charisma(ch), level(lvl), male(gender), name(name){
	//this->name = new char(strlen(name) + 1);
	//strncpy(this->name, name, (strlen(name) + 1));
	this->isUsingMeleeWeapon = 1;
	this->modAtrFromRase();	
	this->setBasicAttack();
	this->setSpeed(); 
	this->hp = this->classHP() + this->constitution.printMod();
	this->setST();
	this->setArmor();
	this->leftMove = printSpeed()+1;

	this->init = this->dexterity.printMod();

	if (this->PlayerRase == rase::dwarf && male == true){
		avatar.loadFromFile("dwarf.png");
		avatarSprite.setTexture(avatar);
		icon.loadFromFile("dwarf_icon.png");
		iconSprite.setTexture(icon);
	}
	if (this->PlayerRase == rase::elf && male == false){
		avatar.loadFromFile("elf_female.png");		
		avatarSprite.setTexture(avatar);
		icon.loadFromFile("elf_icon.png");
		iconSprite.setTexture(icon);
}
	if (this->PlayerRase == rase::human && male == true){
		avatar.loadFromFile("human.png");		
		avatarSprite.setTexture(avatar);
		icon.loadFromFile("human_icon.png");
		iconSprite.setTexture(icon);
}
};


string Player::printName(){
	return (this->name);
}


int Player::printAC(){
	return(this->ac.printAC());
}

string Player::printStr(){
	int val = this->strenght.printAb();
	int mod = this->strenght.printMod();
	return (to_string(val) + "  " + "(" + to_string(mod) + ")");
}

string Player::printDex(){
	int val = this->dexterity.printAb();
	int mod = this->dexterity.printMod();
	return (to_string(val) + "  " + "(" + to_string(mod) + ")");
}

string Player::printCon(){
	int val = this->constitution.printAb();
	int mod = this->constitution.printMod();
	return (to_string(val) + "  " + "(" + to_string(mod) + ")");
}

string Player::printInt(){
	int val = this->intelligence.printAb();
	int mod = this->intelligence.printMod();
	return (to_string(val) + "  " + "(" + to_string(mod) + ")");
}

string Player::printWis(){
	int val = this->wisdom.printAb();
	int mod = this->wisdom.printMod();
	return (to_string(val) + "  " + "(" + to_string(mod) + ")");
}

string Player::printCha(){
	int val = this->charisma.printAb();
	int mod = this->charisma.printMod();
	return (to_string(val) + "  " + "(" + to_string(mod) + ")");
}

void Player::setArmor(){
	if (isMeleeWeapon()){
	if (this->dexterity.printMod() > this->playerArmour.printMaxDex())
		this->ac.getAC(this->playerArmour.printMaxDex() + this->getShield().getAC() + this->playerArmour.getAC());
	else
		this->ac.getAC(this->dexterity.printMod() + this->getShield().getAC() + this->playerArmour.getAC());
	}
	else
	if (this->dexterity.printMod() > this->playerArmour.printMaxDex())
		this->ac.getAC(this->playerArmour.printMaxDex() + this->playerArmour.getAC());
	else
		this->ac.getAC(this->dexterity.printMod() + this->playerArmour.getAC());
}

string Player::printClassName(){
	if (this->PlayerCl == playerClass::fighter)
		return ("Wojownik");
	else if (this->PlayerCl == playerClass::hunter)
		return ("Tropiciel");
	else if (this->PlayerCl == playerClass::priest)
		return ("Kap豉n");
	else
		return("Czarownik");
}
	
string Player::printRaseName(){
	if (this->PlayerRase == rase::human)
		return ("Ludzki");
	else if(this->PlayerRase == rase::elf)
		return ("Elficki");
	else 
		return ("Krasnoludzki");
}

void Player::setBasicAttack(){
	if (this->PlayerCl == playerClass::fighter)
		this->basicAttack = 1;
	else
		this->basicAttack = 0;
}

void Player::setST(){
	if (this->PlayerCl == playerClass::fighter){
		this->fortitude.setVal(this->level.printStHigh() + this->constitution.printMod());
		this->reflex.setVal(this->level.printStLow() + this->dexterity.printMod());
		this->will.setVal(this->level.printStLow() + this->wisdom.printMod());
	}
	else if (this->PlayerCl == playerClass::hunter){
		this->fortitude.setVal(this->level.printStHigh() + this->constitution.printMod());
		this->reflex.setVal(this->level.printStHigh()+ this->dexterity.printMod());
		this->will.setVal(this->level.printStLow() + this->wisdom.printMod());
	}
	else if (this->PlayerCl == playerClass::priest){
		this->fortitude.setVal(this->level.printStHigh() + this->constitution.printMod());
		this->reflex.setVal(this->level.printStLow()+ this->dexterity.printMod());
		this->will.setVal(this->level.printStHigh() + this->wisdom.printMod());
	}
	else {
		this->fortitude.setVal(this->level.printStLow() + this->constitution.printMod());
		this->reflex.setVal(this->level.printStLow() + this->dexterity.printMod());
		this->will.setVal(this->level.printStHigh() + this->wisdom.printMod());
	}
}

int Player::printSTFor(){
	return(this->fortitude.printVal());
}

int Player::printSTRef(){
	return(this->reflex.printVal());
}

int Player::printSTWl(){
	return(this->will.printVal());
}

int Player::printBasicAttack(){
	return(this->basicAttack+this->strenght.printMod());
}

int Player::printDistanceAttack(){
	return(this->basicAttack + this->dexterity.printMod());
}


int Player::classHP(){
	if (this->PlayerCl == playerClass::fighter)
		return (10);
	else if (this->PlayerCl == playerClass::wizard)
		return (4);
	else
		return(8);
}

int Player::printLvl(){
	return(this->level.printLvl());
};

int Player::printExp(){
	return(this->level.printExp());
};

int Player::printExpToLv(){
	return(this->level.printExpToLv());
};

void Player::modAtrFromRase(){

	if (this->PlayerRase == rase::dwarf){
		this->constitution.setValue(this->constitution.printAb() + 2);
		this->charisma.setValue(this->wisdom.printAb() - 2);
	}
	else if (this->PlayerRase == rase::elf){
		this->dexterity.setValue(this->dexterity.printAb() + 2);
		this->constitution.setValue(this->constitution.printAb() - 2);
	}
}

int Player::setSpeed() {
	if (this->PlayerRase == rase::dwarf || this->playerArmour.printSpeed() == 4)
		return this->speed = 4;
	else
		return this->speed = 6;
}

int Player::printSpeed(){
	return this->speed;
}


sf::Sprite &Player::printAvatar(){
		return(this->avatarSprite);
	}

sf::Sprite &Player::printIcon(){
	return this->iconSprite;
}

void Player::setMainWeapon(Weapon weap){
	if (weap.isSoldier() == false || (weap.isSoldier() && (this->PlayerCl == playerClass::fighter || this->PlayerCl == playerClass::hunter)))
	this->mainWeapon = weap;
}

void Player::setDistanceWeapon(DistanceWeapon weap){
	if (weap.isSoldier() == false || (weap.isSoldier() && (this->PlayerCl == playerClass::fighter || this->PlayerCl == playerClass::hunter)))
	this->secondWeapon = weap;
}

Level& Player::getLevel(){
	return this->level;
}

Weapon Player::getMainWeapon(){
	return this->mainWeapon;
}

DistanceWeapon Player::getSecondWeapon(){
	return this->secondWeapon;
}

void Player::setShield(Shield shie)
{
	if (this->mainWeapon.isTwoHanded() == false && this->PlayerCl != playerClass::wizard){
		this->playerShield = shie;
		this->setArmor();
	}
}

Shield Player::getShield(){
	return this->playerShield;
}

Armour Player::getArmour(){
	return this->playerArmour;
}

Hp &Player::getHp(){
	return this->hp;
}


void Player::setArmour(Armour arm){
	if (arm.isHeavy() != true && this->PlayerCl != playerClass::wizard)
		this->playerArmour = arm;
	else if (arm.isHeavy() == true && this->PlayerCl == playerClass::fighter)
		this->playerArmour = arm;
	setArmor();
	setSpeed();
}

void Player::changeWeapon(){
	if (isMeleeWeapon())
		isUsingMeleeWeapon = 0;
	else 
		isUsingMeleeWeapon = 1;
	setArmor();
}

bool Player::isMeleeWeapon(){
	return this->isUsingMeleeWeapon;
}

void Player::setPosition(int x, int y, Map& mapa){
	if (isCrossMove && wasCrossMove == false){
			this->leftMove--;
			//this->leftMove--;
			//position = make_pair(x, y);
			this->isCrossMove = false;
			this->wasCrossMove = true;
		}
	else if (isCrossMove && wasCrossMove){
		//this->leftMove--;
		//position = make_pair(x, y);
		this->isCrossMove = false;
		this->wasCrossMove = false;
	}

	this->leftMove--;
	position = make_pair(x, y);
	mapa.addPosition(position);
}

void Player::endTurn(){
	this->leftMove = 0;
}

int Player::printLeftMove(){
	return leftMove;
}

void Player::isCrossedMove(){
	isCrossMove = true;
}

bool Player::wasCrossedMove(){
	return wasCrossMove;
}

void Player::setCrossedMove(){
	this-> wasCrossMove = false;
}

void Player::setLeftMove(){
	leftMove = this->printSpeed();
}

pair<int, int> Player::getPosition(){
	return this->position;
}



////
NPC::NPC(){
	NPC(false, Ability(0), Ability(0), Ability(0), Ability(0), Ability(0), Ability(0), Level(0), Armor());
}
NPC::NPC(bool archer, Ability s, Ability d, Ability c, Ability i, Ability w, Ability ch, Level lvl, Armor arcl) :strenght(s), dexterity(d), constitution(c), intelligence(i), wisdom(w), charisma(ch), level(lvl){
	this->isUsingMeleeWeapon = 1;
	this->modAtrFromRase();
	this->setBasicAttack();
	this->setSpeed();
	this->hp = this->classHP() + this->constitution.printMod();
	this->setST();
	this->setArmor();
	this->leftMove = printSpeed() + 1;
	this->init = this->dexterity.printMod();
	this->PlayerRase = rase::human;
	this->male = true;

	if (archer){
		this->PlayerCl = playerClass::hunter;
		icon.loadFromFile("archer_icon.png");
		iconSprite.setTexture(icon);
		this->expValue = 120;
	}
	else{
		this->PlayerCl = playerClass::fighter;
		icon.loadFromFile("soldier_icon.png");
		iconSprite.setTexture(icon);
		this->expValue = 100;
	}
	
};



int NPC::printAC(){
	return(this->ac.printAC());
}

void NPC::setArmor(){
	if (isMeleeWeapon()){
		if (this->dexterity.printMod() > this->playerArmour.printMaxDex())
			this->ac.getAC(this->playerArmour.printMaxDex() + this->getShield().getAC() + this->playerArmour.getAC());
		else
			this->ac.getAC(this->dexterity.printMod() + this->getShield().getAC() + this->playerArmour.getAC());
	}
	else
	if (this->dexterity.printMod() > this->playerArmour.printMaxDex())
		this->ac.getAC(this->playerArmour.printMaxDex() + this->playerArmour.getAC());
	else
		this->ac.getAC(this->dexterity.printMod() + this->playerArmour.getAC());
}




void NPC::setBasicAttack(){
	if (this->PlayerCl == playerClass::fighter)
		this->basicAttack = 1;
	else
		this->basicAttack = 0;
}

void NPC::setST(){
	if (this->PlayerCl == playerClass::fighter){
		this->fortitude.setVal(this->level.printStHigh() + this->constitution.printMod());
		this->reflex.setVal(this->level.printStLow() + this->dexterity.printMod());
		this->will.setVal(this->level.printStLow() + this->wisdom.printMod());
	}
	else if (this->PlayerCl == playerClass::hunter){
		this->fortitude.setVal(this->level.printStHigh() + this->constitution.printMod());
		this->reflex.setVal(this->level.printStHigh() + this->dexterity.printMod());
		this->will.setVal(this->level.printStLow() + this->wisdom.printMod());
	}
	else if (this->PlayerCl == playerClass::priest){
		this->fortitude.setVal(this->level.printStHigh() + this->constitution.printMod());
		this->reflex.setVal(this->level.printStLow() + this->dexterity.printMod());
		this->will.setVal(this->level.printStHigh() + this->wisdom.printMod());
	}
	else {
		this->fortitude.setVal(this->level.printStLow() + this->constitution.printMod());
		this->reflex.setVal(this->level.printStLow() + this->dexterity.printMod());
		this->will.setVal(this->level.printStHigh() + this->wisdom.printMod());
	}
}

int NPC::printSTFor(){
	return(this->fortitude.printVal());
}

int NPC::printSTRef(){
	return(this->reflex.printVal());
}

int NPC::printSTWl(){
	return(this->will.printVal());
}

int NPC::printBasicAttack(){
	return(this->basicAttack + this->strenght.printMod());
}

int NPC::printDistanceAttack(){
	return(this->basicAttack + this->dexterity.printMod());
}


int NPC::classHP(){
	if (this->PlayerCl == playerClass::fighter)
		return (10);
	else if (this->PlayerCl == playerClass::wizard)
		return (4);
	else
		return(8);
}


void NPC::modAtrFromRase(){

	if (this->PlayerRase == rase::dwarf){
		this->constitution.setValue(this->constitution.printAb() + 2);
		this->charisma.setValue(this->wisdom.printAb() - 2);
	}
	else if (this->PlayerRase == rase::elf){
		this->dexterity.setValue(this->dexterity.printAb() + 2);
		this->constitution.setValue(this->constitution.printAb() - 2);
	}
}

int NPC::setSpeed() {
	if (this->PlayerRase == rase::dwarf || this->playerArmour.printSpeed() == 4)
		return this->speed = 4;
	else
		return this->speed = 6;
}

int NPC::printSpeed(){
	return this->speed;
}


sf::Sprite &NPC::printIcon(){
	return this->iconSprite;
}

void NPC::setMainWeapon(Weapon weap){
	if (weap.isSoldier() == false || (weap.isSoldier() && (this->PlayerCl == playerClass::fighter || this->PlayerCl == playerClass::hunter)))
		this->mainWeapon = weap;
}

void NPC::setDistanceWeapon(DistanceWeapon weap){
	if (weap.isSoldier() == false || (weap.isSoldier() && (this->PlayerCl == playerClass::fighter || this->PlayerCl == playerClass::hunter)))
		this->secondWeapon = weap;
}

Weapon NPC::getMainWeapon(){
	return this->mainWeapon;
}

DistanceWeapon NPC::getSecondWeapon(){
	return this->secondWeapon;
}

void NPC::setShield(Shield shie)
{
	if (this->mainWeapon.isTwoHanded() == false && this->PlayerCl != playerClass::wizard){
		this->playerShield = shie;
		this->setArmor();
	}
}

Shield NPC::getShield(){
	return this->playerShield;
}

Armour NPC::getArmour(){
	return this->playerArmour;
}

Hp &NPC::getHp(){
	return this->hp;
}

void NPC::setArmour(Armour arm){
	if (arm.isHeavy() != true && this->PlayerCl != playerClass::wizard)
		this->playerArmour = arm;
	else if (arm.isHeavy() == true && this->PlayerCl == playerClass::fighter)
		this->playerArmour = arm;
	setArmor();
	setSpeed();
}

void NPC::changeWeapon(){
	if (isMeleeWeapon())
		isUsingMeleeWeapon = 0;
	else
		isUsingMeleeWeapon = 1;
	setArmor();
}

bool NPC::isMeleeWeapon(){
	return this->isUsingMeleeWeapon;
}

void NPC::setPosition(int x, int y, Map& mapa){
	if (isCrossMove && wasCrossMove == false){
		this->leftMove--;
		//this->leftMove--;
		//position = make_pair(x, y);
		this->isCrossMove = false;
		this->wasCrossMove = true;
	}
	else if (isCrossMove && wasCrossMove){
		//this->leftMove--;
		//position = make_pair(x, y);
		this->isCrossMove = false;
		this->wasCrossMove = false;
	}

	this->leftMove--;
	position = make_pair(x, y);
	mapa.addPosition(position);
}

int NPC::printLeftMove(){
	return leftMove;
}

void NPC::isCrossedMove(){
	isCrossMove = true;
}

bool NPC::wasCrossedMove(){
	return wasCrossMove;
}

void NPC::setCrossedMove(){
	this->wasCrossMove = false;
}

void NPC::setLeftMove(){
	leftMove = this->printSpeed();
}

pair<int, int> NPC::getPosition(){
	return this->position;
}

int NPC::returnExpValue(){
	return this->expValue;
}

void NPC::endTurn(){
	this->leftMove = 0;
}


void Player::moveLeft(Map&mapa, sf::Text& text){
	mapa.freePosition(this->getPosition());
	this->setPosition(this->getPosition().first - 1, this->getPosition().second, mapa);
	this->printIcon().setPosition(30 * this->getPosition().first, 30 * this->getPosition().second);
	text.setString(L"Pozosta這 " + to_string(this->printLeftMove()));
}

void Player::moveLeftTop(Map&mapa, Text& text){
	mapa.freePosition(this->getPosition());
	this->isCrossedMove();
	this->setPosition(this->getPosition().first - 1, this->getPosition().second - 1, mapa);
	this->printIcon().setPosition(30 * this->getPosition().first, 30 * this->getPosition().second);
	text.setString(L"Pozosta這 " + to_string(this->printLeftMove()));
}

void Player::moveLeftDown(Map&mapa, Text& text){
	mapa.freePosition(this->getPosition());
	this->isCrossedMove();
	this->setPosition(this->getPosition().first - 1, this->getPosition().second + 1, mapa);
	this->printIcon().setPosition(30 * this->getPosition().first, 30 * this->getPosition().second);
	text.setString(L"Pozosta這 " + to_string(this->printLeftMove()));
}

void Player::moveRight(Map&mapa, Text& text){
	mapa.freePosition(this->getPosition());
	this->setPosition(this->getPosition().first + 1, this->getPosition().second, mapa);
	this->printIcon().setPosition(30 * this->getPosition().first, 30 * this->getPosition().second);
	text.setString(L"Pozosta這 " + to_string(this->printLeftMove()));
}

void Player::moveRightTop(Map&mapa, Text& text){
	mapa.freePosition(this->getPosition());
	this->isCrossedMove();
	this->setPosition(this->getPosition().first + 1, this->getPosition().second - 1, mapa);
	this->printIcon().setPosition(30 * this->getPosition().first, 30 * this->getPosition().second);
	text.setString(L"Pozosta這 " + to_string(this->printLeftMove()));
}

void Player::moveRightDown(Map&mapa, Text& text){
	mapa.freePosition(this->getPosition());
	this->isCrossedMove();
	this->setPosition(this->getPosition().first + 1, this->getPosition().second + 1, mapa);
	this->printIcon().setPosition(30 * this->getPosition().first, 30 * this->getPosition().second);
	text.setString(L"Pozosta這 " + to_string(this->printLeftMove()));
}

void Player::moveTop(Map&mapa, Text& text){
	mapa.freePosition(this->getPosition());
	this->setPosition(this->getPosition().first, this->getPosition().second - 1, mapa);
	this->printIcon().setPosition(30 * this->getPosition().first, 30 * this->getPosition().second);
	text.setString(L"Pozosta這 " + to_string(this->printLeftMove()));
}

void Player::moveDown(Map&mapa, Text& text){
	mapa.freePosition(this->getPosition());
	this->setPosition(this->getPosition().first, this->getPosition().second + 1, mapa);
	this->printIcon().setPosition(30 * this->getPosition().first, 30 * this->getPosition().second);
	text.setString(L"Pozosta這 " + to_string(this->printLeftMove()));
}