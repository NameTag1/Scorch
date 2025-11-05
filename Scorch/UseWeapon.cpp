#include "UseWeapon.h"
#include "WeaponWielder.h"
#include <iostream>

UseWeapon::UseWeapon(std::string action)
: mString(action)
, Action(Live)
{
}

UseWeapon::UseWeapon(std::string action, Action::Type runOnce)
: mString(action)
, Action(runOnce)
{
}

void UseWeapon::update(sf::Time dt, CommandQueue& Commands, SceneNode& target) 
{
	WeaponWielder* a = dynamic_cast<WeaponWielder*>(&target);
	a->useWeapon(mString, target);
	std::cout << "USING\n";
}

bool UseWeapon::isFinnished() {
	return true;
};

void UseWeapon::reset() {
	
}