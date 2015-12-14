#include "Dice.h"

int Dice::rollDice(int size){ return (rand() % size + 1); }
int Dice::returnSize(){ return(this->size); }
Dice::Dice(int siz) :size(siz){};
Dice::Dice(){
	size = 0;
};