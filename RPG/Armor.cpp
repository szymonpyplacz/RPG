#pragma once
#include "Armor.h"
#include <SFML\Graphics.hpp>

void Armor::getAC(int a){
	this->ac = 10+a;
}

Armor::Armor() {
	this->ac = 10;
}

int Armor::printAC(){
return(this->ac);
}
