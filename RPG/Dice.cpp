#include "Dice.h"
#include <random>

int Dice::rollDice(){ 
	std::default_random_engine gen;
	std::uniform_int_distribution<int> dist(1, size);
	return  dist(gen);
}

int Dice::returnSize(){ return(this->size); }
Dice::Dice(int siz) :size(siz){};
Dice::Dice(){
	size = 0;
};