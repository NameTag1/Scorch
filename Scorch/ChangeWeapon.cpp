#include "ChangeWeapon.h"

#include "WeaponWielder.h"

ChangeWeapon::ChangeWeapon(int changeBy)
	: mChangeBy(changeBy)
	, Action(Live)
{
}

ChangeWeapon::ChangeWeapon(int changeBy, Action::Type runOnce)
	: mChangeBy(changeBy)
	, Action(runOnce)
{
}

void ChangeWeapon::update(sf::Time dt, CommandQueue& Commands, SceneNode& target)
{
	WeaponWielder* a = dynamic_cast<WeaponWielder*>(&target);
	a->nextWeapon(mChangeBy);
	//std::cout << "USING\n";
}

bool ChangeWeapon::isFinnished() {
	return true;
};

void ChangeWeapon::reset() {

}