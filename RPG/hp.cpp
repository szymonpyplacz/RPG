#pragma once
#include <SFML\Graphics.hpp>
#include <Windows.h>
#include <string>
#include "Hp.h"

void Hp::getHp(int newHp){
	this->hp = newHp;
}

void Hp::getHpMax(int newHpMax){
	hpMax = newHpMax;
}

void Hp::getDmg(int dmg){
	if (dmg > printHP())
		dmg = printHP();
	this->hp -= dmg;
}

int Hp::printHP(){
	return(this->hp);
}

int Hp::printMaxHP(){
	return(this->hpMax);
}

Hp::Hp(int maxhp) : hpMax(maxhp), hp(maxhp){

};

Hp::Hp(){
}

sf::Sprite& Hp::printSprite(){
	if (printHP() >= 0.9*printMaxHP()){
	picture.loadFromFile("hp100.png");
	pictureSprite.setTexture(picture);
	}
	else if (printHP() > 0.6*printMaxHP()){
		picture.loadFromFile("hp80.png");
		pictureSprite.setTexture(picture);
	}
	else if (printHP() > 0.4*printMaxHP()){
		picture.loadFromFile("hp60.png");
		pictureSprite.setTexture(picture);
	}
	else if (printHP() > 0.2*printMaxHP()){
		picture.loadFromFile("hp40.png");
		pictureSprite.setTexture(picture);
	}
	else if (printHP() > 0){
		picture.loadFromFile("hp20.png");
		pictureSprite.setTexture(picture);
	}
	else {
		picture.loadFromFile("hp0.png");
		pictureSprite.setTexture(picture);
	}
	return pictureSprite;
}

sf::Texture& Hp::printTexture(){
	if (printHP() >= 0.9*printMaxHP()){
		picture.loadFromFile("hp100.png");
	}
	else if (printHP() > 0.6*printMaxHP()){
		picture.loadFromFile("hp80.png");
	}
	else if (printHP() > 0.4*printMaxHP()){
		picture.loadFromFile("hp60.png");
	}
	else if (printHP() > 0.2*printMaxHP()){
		picture.loadFromFile("hp40.png");
	}
	else if (printHP() > 0){
		picture.loadFromFile("hp20.png");
	}
	else {
		picture.loadFromFile("hp0.png");
	}
	return picture;
}
