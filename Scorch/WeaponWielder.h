#pragma once

#ifndef weaponWielderh
#define weaponWielderh

#include "SceneNode.hpp"
#include "Attacker.h"
#include "Weapon.h"

class WeaponWielder
{
public:
	WeaponWielder();
	void update(sf::Time dt, CommandQueue& Commands, SceneNode& target);

	std::vector<Textures::ID> weaponIconsHeld();
	std::vector<Textures::ID> weaponIcons();

	void pushWeapon(Weapon* weapon);
	void useWeapon(std::string selectedAttack, SceneNode& target);

	void selectWeapon(int weapon);
	void nextWeapon(int increment);

private:
	int selected;
	int lastSelected;
	int maxWeapons;
	std::vector<Weapon*> held;
	std::vector<Weapon*> weapons;
};

#endif // !weaponWielderh
