#pragma once
#include <SFML\Graphics.hpp>
#include <Windows.h>
#include <string>
#include "Hp.h"

void Hp::getHp(int newHp){
	this->hp = newHp;
	if (newHp > 0){
		this->alive = true;
	}
}

void Hp::getHpMax(int newHpMax){
	this->hpMax = newHpMax;
}

void Hp::getDmg(int dmg){
	this->hp -= dmg;
	if (this->hp < 0)
		alive = false;
}

int Hp::printHP(){
	return(this->hp);
}

int Hp::printMaxHP(){
	return(this->hpMax);
}

Hp::Hp(int maxhp) : hpMax(maxhp), alive(true), hp(maxhp){};
