#include "SavingThrows.h"

SavingThrow::SavingThrow(int a) :value(a){};

void SavingThrow::setVal(int a){
	this->value = a;
}
int SavingThrow::printVal(){
	return (this->value);
}