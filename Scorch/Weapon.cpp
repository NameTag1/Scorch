#include "Weapon.h"
#include "Actionable.h"
#include "ResourceIdentifiers.hpp"
#include "ResourceHolder.hpp"
#include "Player_Entity.h"
#include <iostream>

Weapon::Weapon(const TextureHolder& textures, Category::Type type)
: mIcon(Textures::Default)
, left(false)
, up(false)
{
}

void Weapon::updateCurrent(sf::Time dt, CommandQueue& commands)
{
	
}

void Weapon::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{

}

void Weapon::update(sf::Time dt, CommandQueue& Commands, SceneNode& target) 
{

}


void Weapon::setDirection(bool left, bool up)
{
	if (Weapon::left != left || Weapon::up != up) {
		Weapon::left = left;
		Weapon::up = up;
		flip();
	}
}

void Weapon::flip()
{

}

void Weapon::interact(Player_Entity& player) 
{
	player.pushWeapon(this);
}

void Weapon::useWeapon(std::string selectedAttack, SceneNode& target)
{
	if (mActions[selectedAttack]) { //If weapon has attack of specified slot, can be null, eg. a bow not having a throw attack
		Actionable* actionable = dynamic_cast<Actionable*>(&target);
		Action* a = mActions[selectedAttack]; //Copies Action
		actionable->pushAction(a);
	}
}

Textures::ID Weapon::getIcon()
{
	return mIcon;
}

std::vector<unsigned int> Weapon::getCategory() const 
{
	std::vector<unsigned int> i(Interactable::getCategory());
	i.push_back(Category::Weapon);
	return i;
}

std::map<std::string, Action*> Weapon::getActions()
{
	return mActions;
}

std::map<std::string, Attack*> Weapon::getAttacks()
{
	return mAttacks;
}
