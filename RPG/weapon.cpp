#include "Weapon.h"

Weapon::Weapon(int dmg, bool soldier, bool twoHanded, bool light, int crit, int crRange, listOfWeapons number) :Damage(dmg), soldier(soldier), twoHanded(twoHanded), light(light), critic(crit), criticRange(crRange){

	if (number == listOfWeapons::Dagger){
		name = L"Sztylet";
		picture.loadFromFile("dagger.png");
		pictureSprite.setTexture(picture);
	}

	else if (number == listOfWeapons::ShortSword){
		name = L"Kr�tki miecz";
		picture.loadFromFile("ShortSword.png");
		pictureSprite.setTexture(picture);
	}
	else if (number == listOfWeapons::SmallAxe){
		name = L"Toporek";
		picture.loadFromFile("smallAxe.png");
		pictureSprite.setTexture(picture);
	}
	else if (number == listOfWeapons::Longsword){
		name = L"D�ugi miecz";
		picture.loadFromFile("longsword.png");
		pictureSprite.setTexture(picture);
	}
	else if (number == listOfWeapons::Spear){
		name = L"W��cznia";
		picture.loadFromFile("spear.png");
		pictureSprite.setTexture(picture);
	}
	else if (number == listOfWeapons::TwoHandedSword){
		name = L"Dwur�czny miecz";
		picture.loadFromFile("THSword.png");
		pictureSprite.setTexture(picture);
	}
	else if (number == listOfWeapons::TwoHandedAxe){
		name = L"Dwur�czny top�r";
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
	name = L"Pi��";
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



DistanceWeapon::DistanceWeapon(int dmg, bool soldier, bool twoHanded, bool light, int crit, int crRange, int range, int missles, listOfDistanceWeapons number) : Damage(dmg), soldier(soldier), twoHanded(twoHanded), light(light), critic(crit), criticRange(crRange), missles(missles), range(range){

	if (number == listOfDistanceWeapons::Bow){
		name = L"Kr�tki �uk";
		picture.loadFromFile("bow.png");
		pictureSprite.setTexture(picture);
	}
	else if (number == listOfDistanceWeapons::Crossbow){
		name = L"Kusza";
		picture.loadFromFile("bow.png");
		pictureSprite.setTexture(picture);
	}
	else if (number == listOfDistanceWeapons::Longbow){
		name = L"D�ugi �uk";
		picture.loadFromFile("bow.png");
		pictureSprite.setTexture(picture);
	}
	else if (number == listOfDistanceWeapons::Slingshot){
		name = L"Proca";
		picture.loadFromFile("bow.png");
		pictureSprite.setTexture(picture);
	}
}

DistanceWeapon::DistanceWeapon(){
	Damage = Dice(0);
	soldier = false;
	twoHanded = true;
	light = true;
	critic = 2;
	criticRange = 20;
	name = L"nic";
	picture.loadFromFile("fist.png");
	pictureSprite.setTexture(picture);
}
