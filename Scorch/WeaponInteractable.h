#pragma once

#include "Interactable.h"
#include "Weapon.h"

#include <memory>

class WeaponInteractable : public Interactable
{
public:


private:
	std::unique_ptr<Weapon> mWeapon;
};

