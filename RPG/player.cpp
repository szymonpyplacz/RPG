#include "player.h"
#include "Dice.h"
#include <algorithm>
#include "Weapon.h"
#pragma once

Player::Player(playerClass plcl, rase plRase, Ability s, Ability d, Ability c, Ability i, Ability w, Ability ch, Level lvl, Armor arcl, bool gender, char* name) : PlayerCl(plcl), PlayerRase(plRase), strenght(s), dexterity(d), constitution(c), intelligence(i), wisdom(w), charisma(ch), level(lvl), male(gender){
	this->name = new char(strlen(name) + 1);
	strncpy(this->name, name, (strlen(name) + 1));
	
	this->modAtrFromRase();
	
	this->setBasicAttack();

	this->setSpeed(); 

	this->hp = this->classHP() + this->constitution.printMod();
	this->setST();
	this->setArmor();

	this->init = this->dexterity.printMod();

	if (this->PlayerRase == 2 && male == true){
		avatar.loadFromFile("dwarf.jpg");
		avatarSprite.setTexture(avatar);
	}
	if (this->PlayerRase == 1 && male == false){
		avatar.loadFromFile("elf_female.png");		
		avatarSprite.setTexture(avatar);
}
	if (this->PlayerRase == 0 && male == true){
		avatar.loadFromFile("human.png");		
		avatarSprite.setTexture(avatar);
}

};

string Player::printName(){
	return (this->name);
}

int Player::printHpMax(){
	return(this->hp.printMaxHP());
}

int Player::printHpNow(){
	return(this->hp.printHP());
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
	this->ac.getAC(this->dexterity.printMod());
}

string Player::printClassName(){
	if (this->PlayerCl == 0)
		return ("Wojownik");
	else if(this->PlayerCl == 1)
		return ("Tropiciel");
	else if(this->PlayerCl == 2)
		return ("Kap³an");
	else
		return("Czarownik");
}
	
string Player::printRaseName(){
	if (this->PlayerRase == 0)
		return ("Cz³owiek");
	else if(this->PlayerRase == 1)
		return ("Elf");
	else 
		return ("Krasnolud");
}

void Player::setBasicAttack(){
	if (this->PlayerCl == 0)
		this->basicAttack = 1;
	else
		this->basicAttack = 0;
}

void Player::setST(){
	if (this->PlayerCl == 0){
		this->fortitude.setVal(this->level.printStHigh() + this->constitution.printMod());
		this->reflex.setVal(this->level.printStLow() + this->dexterity.printMod());
		this->will.setVal(this->level.printStLow() + this->wisdom.printMod());
	}
	else if (this->PlayerCl == 1){
		this->fortitude.setVal(this->level.printStHigh() + this->constitution.printMod());
		this->reflex.setVal(this->level.printStHigh()+ this->dexterity.printMod());
		this->will.setVal(this->level.printStLow() + this->wisdom.printMod());
	}
	else if (this->PlayerCl == 2){
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
	if (this->PlayerCl == 0)
		return (10);
	else if (this->PlayerCl == 3)
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

	if (this->PlayerRase == 2){
		this->constitution.setValue(this->constitution.printAb() + 2);
		this->charisma.setValue(this->wisdom.printAb() - 2);
	}
	else if (this->PlayerRase == 1){
		this->dexterity.setValue(this->dexterity.printAb() + 2);
		this->constitution.setValue(this->constitution.printAb() - 2);
	}
}

int Player::setSpeed() {
	if (this->PlayerRase == 2)
		return this->speed = 4;
	else
		return this->speed = 6;
}

int Player::printSpeed(){
	return this->speed;
}

//Weapon Player::mainWeapon{
//	return this->mainWeapon;
//}

sf::Sprite Player::printAvatar(){
	return(this->avatarSprite);
}