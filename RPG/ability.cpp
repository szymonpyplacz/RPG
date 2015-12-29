#include "Ability.h"

Ability::Ability(){
	Ability(0);
}

void Ability::setValue(int value)
{
	this->value = value;
	int help = value - 10;
	this->mod = help / 2;
}

Ability::Ability(int val): value(val){
	int help = value - 10;
	this->mod = help / 2;
};

int Ability::printAb(){
	return(this->value);
}

int Ability::printMod(){
	return(this->mod);
}