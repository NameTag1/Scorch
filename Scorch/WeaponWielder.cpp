#include "WeaponWielder.h"
#include <iostream>

WeaponWielder::WeaponWielder()
	: selected(0)
	, lastSelected(-1)
	, maxWeapons(3)
{
	for (int i = 0; i < maxWeapons; i++) {
		weapons.push_back(nullptr);
	}
}

void WeaponWielder::update(sf::Time dt, CommandQueue& Commands, SceneNode& target)
{
	Movable* entity = dynamic_cast<Movable*>(&target);
	bool left = (entity->lastKnownDirection().x <= 0) ? true : false;
	bool up = (entity->lastKnownDirection().y <= 0) ? true : false;

	if (weapons[selected] != nullptr) {
		weapons[selected]->setDirection(left, up);

		if (lastSelected != selected) {
			Attacker* attacker = dynamic_cast<Attacker*>(&target);
			attacker->clearAttacks();

			attacker->pushAttack(weapons[selected]->getAttacks());
			lastSelected = selected;
			//target.detachChild(*weapons[lastSelected]); Last selected not always still attached
			target.attachChild(SceneNode::Ptr(weapons[selected]));
		}
	}
}

std::vector<Textures::ID> WeaponWielder::weaponIcons()
{
	std::vector<Textures::ID> i;
	for (Weapon* x : weapons) {
		//std::cout << x->getCategory()[1];
		if (x != nullptr) {
			i.push_back(x->getIcon());
		}
		else {
			i.push_back(Textures::Default);
		}
	}
	return i;
}

std::vector<Textures::ID> WeaponWielder::weaponIconsHeld()
{
	std::vector<Textures::ID> i;
	for (Weapon* x : held) {
		//std::cout << x->getCategory()[1];
		if (x != nullptr) {
			i.push_back(x->getIcon());
		}
		else {
			i.push_back(Textures::Default);
		}
	}
	return i;
}

void WeaponWielder::pushWeapon(Weapon* weapon)
{
	std::cout << "PushedWeapon\n";
	for (int i = 0; i < maxWeapons; i++) {
		if (weapons[i] == nullptr) {
			weapons[i] = weapon;
			return; //Once open slot found, deposites weapon and exits FUNCTION, not just FOR
		}
	}
	held.push_back(weapon); //If no open slots found, put in bag
}

void WeaponWielder::selectWeapon(int weapon)
{
	if (weapon > weapons.size()) {
		selected = weapons.size() - 1;
	}
	else if (weapon < 0) {
		selected = 0;
	}
	else {
		selected = weapon;
	}
}

void WeaponWielder::nextWeapon(int increment)
{
	selected += increment;
	if (selected > weapons.size()) {
		selected = 0;
	}
	else if (selected < 0) {
		selected = weapons.size() - 1;
	}
}

void WeaponWielder::useWeapon(std::string selectedAttack, SceneNode& target)
{
	if (weapons[selected] != nullptr) {
		weapons[selected]->useWeapon(selectedAttack, target);
	}
}