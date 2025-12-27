#include "WeaponWielder.h"

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
	if (!entity) return;

	bool left = (entity->lastKnownDirection().x <= 0) ? true : false;
	bool up = (entity->lastKnownDirection().y <= 0) ? true : false;

	// guard against empty weapons vector and invalid selected index
	if (weapons.empty()) return;
	if (selected < 0 || selected >= static_cast<int>(weapons.size())) selected = 0;

	if (weapons[selected] != nullptr) {
		weapons[selected]->setDirection(left, up);

		if (lastSelected != selected) {
			Attacker* attacker = dynamic_cast<Attacker*>(&target);
			if (attacker) {
				attacker->clearAttacks();
				attacker->pushAttack(weapons[selected]->getAttacks());
			}
			lastSelected = selected;
		}
	}
}

std::vector<Textures::ID> WeaponWielder::weaponIcons()
{
	std::vector<Textures::ID> i;
	for (auto x : weapons) {
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
	for (auto x : held) {
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
	for (int i = 0; i < maxWeapons; i++) {
		if (weapons[i] == nullptr) {
			weapons[i] = weapon;
			return;
		}
	}
	held.push_back(weapon);
}

void WeaponWielder::selectWeapon(int weapon)
{
	if (weapons.empty()) {
		selected = 0;
		return;
	}

	// clamp into [0, size-1]
	if (weapon >= static_cast<int>(weapons.size())) {
		selected = static_cast<int>(weapons.size()) - 1;
	}
	else if (weapon <= 0) {
		selected = 0;
	}
	else {
		selected = weapon;
	}
}

void WeaponWielder::nextWeapon(int increment)
{
	if (weapons.empty()) {
		selected = 0;
		return;
	}

	const int n = static_cast<int>(weapons.size());
	int newIndex = (selected + increment) % n;
	if (newIndex < 0) newIndex += n;
	selected = newIndex;
}

int WeaponWielder::getSelected()
{
	return selected;
}

void WeaponWielder::useWeapon(std::string selectedAttack, SceneNode& target)
{
	if (weapons.empty()) return;
	if (selected < 0 || selected >= static_cast<int>(weapons.size())) return;

	if (weapons[selected] != nullptr) {
		weapons[selected]->useWeapon(selectedAttack, target);
	}
}