#include "Weapon.h"

Weapon::Weapon(int dmg, bool soldier, bool twoHanded, bool light, int crit, int crRange, listOfWeapons number) :Damage(dmg), soldier(soldier), twoHanded(twoHanded), light(light), critic(crit), criticRange(crRange){

	if (number == 1){
		name = L"Sztylet";
		picture.loadFromFile("dagger.png");
		pictureSprite.setTexture(picture);
	}

	else if (number == 2){
		name = L"Krótki miecz";
		picture.loadFromFile("ShortSword.png");
		pictureSprite.setTexture(picture);
	}
	else if (number == 3){
		name = L"Toporek";
		picture.loadFromFile("smallAxe.png");
		pictureSprite.setTexture(picture);
	}
	else if (number == 4){
		name = L"D³ugi miecz";
		picture.loadFromFile("longsword.png");
		pictureSprite.setTexture(picture);
	}
	else if (number == 5){
		name = L"W³ócznia";
		picture.loadFromFile("spear.png");
		pictureSprite.setTexture(picture);
	}
	else if (number == 6){
		name = L"Dwurêczny miecz";
		picture.loadFromFile("THSword.png");
		pictureSprite.setTexture(picture);
	}
	else if (number == 7){
		name = L"Dwurêczny topór";
		picture.loadFromFile("THAxe.png");
		pictureSprite.setTexture(picture);
	}
}

Weapon::Weapon(){
	Damage = Dice(3);
	soldier = false;
	twoHanded = true;
	light = true;
	critic = 2;
	criticRange = 20;
	name = L"Piêœæ";
	picture.loadFromFile("fist.png");
	pictureSprite.setTexture(picture);
}

sf::String Weapon::printWeapon(){
	return(this->name);
}

int Weapon::printWeaponDmg(){
	return(this->Damage.returnSize());
}

int Weapon::printCr(){
	return(this->critic);
}

std::string Weapon::printCrRg(){
	if (this->criticRange == 20)
		return ("20");
	else return("19-20");
}

sf::Sprite Weapon::printSprite(){
	return(this->pictureSprite);
}
