#include "Weapon.h"

Weapon::Weapon(int dmg, bool soldier, bool twoHanded, bool light, int crit, int crRange, listOfWeapons number) :Damage(dmg), soldier(soldier), twoHanded(twoHanded), light(light), critic(crit), criticRange(crRange){
	if (number == listOfWeapons::Fist){
		name = L"Piêœæ";
		picture.loadFromFile("fist.png");
		pictureSprite.setTexture(picture);
	}

	else	if (number == listOfWeapons::Dagger){
		name = L"Sztylet";
		picture.loadFromFile("dagger.png");
		pictureSprite.setTexture(picture);
	}

	else if (number == listOfWeapons::ShortSword){
		name = L"Krótki miecz";
		picture.loadFromFile("ShortSword.png");
		pictureSprite.setTexture(picture);
	}
	else if (number == listOfWeapons::SmallAxe){
		name = L"Toporek";
		picture.loadFromFile("smallAxe.png");
		pictureSprite.setTexture(picture);
	}
	else if (number == listOfWeapons::Longsword){
		name = L"D³ugi miecz";
		picture.loadFromFile("longsword.png");
		pictureSprite.setTexture(picture);
	}
	else if (number == listOfWeapons::Spear){
		name = L"W³ócznia";
		picture.loadFromFile("spear.png");
		pictureSprite.setTexture(picture);
	}
	else if (number == listOfWeapons::TwoHandedSword){
		name = L"Dwurêczny miecz";
		picture.loadFromFile("THSword.png");
		pictureSprite.setTexture(picture);
	}
	else if (number == listOfWeapons::TwoHandedAxe){
		name = L"Dwurêczny topór";
		picture.loadFromFile("THAxe.png");
		pictureSprite.setTexture(picture);
	}
}

Weapon::Weapon(){
	
}

sf::String Weapon::printWeapon(){
	return(name);
}

int Weapon::printWeaponDmg(){
	return(Damage.returnSize());
}

int Weapon::printCr(){
	return(critic);
}

std::string Weapon::printCrRg(){
	if (criticRange == 20)
		return ("20");
	else return("19-20");
}

sf::Sprite Weapon::printSprite(){
	return pictureSprite;
}

bool Weapon::isTwoHanded(){
	return twoHanded;
}

bool Weapon::isSoldier(){
	return soldier;
}

DistanceWeapon::DistanceWeapon(){
	name = L"Brak broni dystansowej";
	picture.loadFromFile("empty.png");
	pictureSprite.setTexture(picture);
}

DistanceWeapon::DistanceWeapon(int dmg, bool soldier,   int crit, int crRange, int range, int missles, listOfDistanceWeapons number) : Damage(dmg), soldier(soldier), twoHanded(twoHanded), critic(crit), criticRange(crRange), missles(missles), range(range){
	twoHanded = 1;

	if (number == listOfDistanceWeapons::Bow){
		name = L"Krótki £uk";
		picture.loadFromFile("bow.png");
		pictureSprite.setTexture(picture);
	}
	else if (number == listOfDistanceWeapons::Crossbow){
		name = L"Kusza";
		picture.loadFromFile("crossbow.png");
		pictureSprite.setTexture(picture);
	}
	else if (number == listOfDistanceWeapons::Longbow){
		name = L"D³ugi £uk";
		picture.loadFromFile("longbow.png");
		pictureSprite.setTexture(picture);
	}
	else if (number == listOfDistanceWeapons::Slingshot){
		name = L"Proca";
		picture.loadFromFile("slingshot.png");
		pictureSprite.setTexture(picture);
	}
}

sf::String DistanceWeapon::printWeapon(){
	return(this->name);
}

int DistanceWeapon::printWeaponDmg(){
	return(this->Damage.returnSize());
}

int DistanceWeapon::printCr(){
	return(this->critic);
}

std::string DistanceWeapon::printCrRg(){
	if (this->criticRange == 20)
		return ("20");
	else return("19-20");
}

sf::Sprite DistanceWeapon::printSprite(){
	return(this->pictureSprite);
}

int DistanceWeapon::printMissles(){
	return this->missles;
}

int DistanceWeapon::printRange(){
	return this->range;
}


Shield::Shield(int ac, listOfShields number) :ac(ac){
	if (number == listOfShields::LightShield){
		name = L"Lekka tarcza";
		picture.loadFromFile("smallShield.png");
		pictureSprite.setTexture(picture);
	}
	else if (number == listOfShields::HeavyShield){
		name = L"Ciê¿ka tarcza";
		picture.loadFromFile("shield.png");
		pictureSprite.setTexture(picture);
	}
}

Shield::Shield(){
	name = L"Brak tarczy";
	picture.loadFromFile("empty.png");
	pictureSprite.setTexture(picture);
}

int Shield::getAC(){
	return this->ac;
}

sf::String Shield::printShield(){
	return this->name;
}

sf::Sprite Shield::printSprite(){
	return this->pictureSprite;
}


Armour::Armour(){
	name = L"Brak zbroi";
	picture.loadFromFile("empty.png");
	pictureSprite.setTexture(picture);
	this->maxDex = 20;
}

Armour::Armour(int ac, int speed, int maxDex, bool heavy, listOfArmour number):ac(ac), speed(speed), maxDex(maxDex), heavy(heavy){
	if (number == listOfArmour::Gambeson){
		name = L"Przeszywanica";
		picture.loadFromFile("gambeson.png");
		pictureSprite.setTexture(picture);
	}
	else if (number == listOfArmour::LeatherArmor){
		name = L"Skórznia";
		picture.loadFromFile("leatherArm.png");
		pictureSprite.setTexture(picture);
	}
	else if (number == listOfArmour::MailShirt){
		name = L"Koszulka kolcza";
		picture.loadFromFile("mailShirt.png");
		pictureSprite.setTexture(picture);
	}
	else if (number == listOfArmour::Chainmail){
		name = L"Kolczuga";
		picture.loadFromFile("chainmail.png");
		pictureSprite.setTexture(picture);
	}
	else if (number == listOfArmour::PlateArmor){
		name = L"Zbroja p³ytowa";
		picture.loadFromFile("plateArmor.png");
		pictureSprite.setTexture(picture);
	}
}

int Armour::getAC(){
	return this->ac;
}

sf::String Armour::printArmour(){
	return this->name;
}

sf::Sprite Armour::printSprite(){
	return this->pictureSprite;
}

bool Armour::isHeavy(){
	return this->heavy;
}

int Armour::printMaxDex(){
	return this->maxDex;
}

int Armour::printSpeed(){
	return this->speed;
}