#pragma once

#include "Action.h"

#include "WeaponWielder.h"

class ChangeWeapon : public Action
{
public:
	ChangeWeapon(int changeBy);
	ChangeWeapon(int changeBy, Action::Type RunOnce);
	virtual void update(sf::Time dt, CommandQueue& Commands, SceneNode& target);
	virtual bool isFinnished();
	virtual void reset();

private:
	int mChangeBy;

	WeaponWielder* mTarget;
};

