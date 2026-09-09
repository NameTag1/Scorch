#include "ChangeWeapon.h"

#include "Utility.hpp"

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
	if (mTarget == nullptr) {
		if (WeaponWielder* castedPtr = dynamic_cast<WeaponWielder*>(&target)) {
			mTarget = castedPtr;
		}
	}
	mTarget->nextWeapon(mChangeBy);
}

bool ChangeWeapon::isFinnished() {
	return true;
};

void ChangeWeapon::reset() {

}