#include "Dice.h"


int Dice::rollDice(){ 
	std::random_device random;
	std::default_random_engine gen(random());
	std::uniform_int_distribution<int> dist(1, size);
	return  dist(gen);
}

int Dice::returnSize(){ return(this->size); }
Dice::Dice(int siz) :size(siz){};
Dice::Dice(){
	size = 0;
};