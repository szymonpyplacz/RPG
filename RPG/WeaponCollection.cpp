#include "WeaponCollection.h"

//int dmg, bool soldier, bool twoHanded, bool light, int crit, int crRange, 
Weapon WeaponCollection::Fist(3, 0, 1, 1, 2, 20, listOfWeapons::Fist);
Weapon WeaponCollection::Dagger(4, 0, 0, 1, 2, 19, listOfWeapons::Dagger);
Weapon WeaponCollection::ShortSword(6, 1, 0, 1, 2, 19, listOfWeapons::ShortSword);
Weapon WeaponCollection::SmallAxe(6, 1, 0, 1, 3, 20, listOfWeapons::SmallAxe);
Weapon WeaponCollection::Longsword(8, 1, 0, 0, 2, 19, listOfWeapons::Longsword);
Weapon WeaponCollection::Spear(8, 0, 1, 0, 3, 20, listOfWeapons::Spear);
Weapon WeaponCollection::TwoHandedSword(10, 1, 1, 0, 2, 19, listOfWeapons::TwoHandedSword);
Weapon WeaponCollection::TwoHandedAxe(12, 1, 1, 0, 3, 20, listOfWeapons::TwoHandedAxe);

//int dmg, bool soldier, int crit, int crRange, int range, int misstle
DistanceWeapon WeaponCollection::Bow(6, 1, 3, 20, 12, 20, listOfDistanceWeapons::Bow);
DistanceWeapon WeaponCollection::Crossbow(8, 1, 2, 19, 16, 10, listOfDistanceWeapons::Crossbow);
DistanceWeapon WeaponCollection::Longbow(8, 1, 3, 20, 20, 20, listOfDistanceWeapons::Longbow);
DistanceWeapon WeaponCollection::Slingshot(4, 1, 2, 20, 10, 10, listOfDistanceWeapons::Slingshot);

Shield WeaponCollection::LightShield(1, listOfShields::LightShield);
Shield WeaponCollection::HeavyShield(2, listOfShields::HeavyShield);