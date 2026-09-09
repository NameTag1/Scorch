#include "UseWeapon.h"
#include "WeaponWielder.h"

#include "Utility.hpp"

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
	if (mTarget == nullptr) {
		if (WeaponWielder* castedPtr = dynamic_cast<WeaponWielder*>(&target)) {
			mTarget = castedPtr;
		}
		//mTarget = safeCast<WeaponWielder*, SceneNode*>(&target);
	}
	mTarget->useWeapon(mString, target);
}

bool UseWeapon::isFinnished() {
	return true;
};

void UseWeapon::reset() {
	
}