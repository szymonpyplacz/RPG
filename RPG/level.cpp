#include "Level.h"
#pragma once

void Level::getExp(int exp) {
	this->exp = exp;
}

void Level::addExp(int add){
	this->exp = this->exp + add;
}

void Level::levelUp(int level){
	if (this->exp > this->expLvl){
		this->level++;
		this->expLvl = +level * 1000;
	}
}

int Level::printStHigh(){
	return(stHigh);
}

int Level::printStLow(){
	return(stLow);
}

int Level::printLvl(){
	return(this->level);
};

int Level::printExp(){
	return(this->exp);
};

int Level::printExpToLv(){
	return(this->expLvl);
};

Level::Level(int exp) :level(1), exp(exp), expLvl(1000){};
Level::Level() :level(1), exp(0), expLvl(1000){};