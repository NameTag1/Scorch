#include "Player_Entity.h"
#include "Utility.hpp"
#include <iostream>

#include "Greatsword.h"
#include "Slash.h"

Player_Entity* Player_Entity::instance = new Player_Entity();

Player_Entity::Player_Entity()
: Platformer(0)
, isAttacking(false)
, isInteracting(false)
, isMarkedForRemoval(false)
, suppressInteracting(false)
{

} //Only used by static instance creator

Player_Entity::Player_Entity(const TextureHolder& resources)
: Platformer(50)
, isMarkedForRemoval(false)
, isAttacking(false)
, isInteracting(false)
, suppressInteracting(false)
, mSprite(resources.get(Textures::Player))
{
	centerOrigin(mSprite);
	//WeaponWielder::pushWeapon(new Greatsword(resources, Category::Enemy));
	//Attacker::pushAttack("Slot 1", new Slash(15, (unsigned int)Category::Enemy, resources));
	instance = this;
}

std::vector<unsigned int> Player_Entity::getCategory() const {
	std::vector<unsigned int> i(Platformer::getCategory());
	i.push_back(Category::Player);
	return i;
};

sf::FloatRect Player_Entity::getBoundingRect() const {
	return getWorldTransform().transformRect(mSprite.getGlobalBounds());
};

bool Player_Entity::markedForRemoval() {
	return isMarkedForRemoval;
};

bool Player_Entity::getInteracting() {
	return isInteracting;
};

void Player_Entity::setInteracting(bool interacting) {
	if (interacting == true) {
		suppressInteracting = true;
	}
	isInteracting = interacting;
}

Player_Entity* Player_Entity::getInstance() {
	return instance;
};

void Player_Entity::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(mSprite, states);
};

void Player_Entity::updateCurrent(sf::Time dt, CommandQueue& Commands) {
	if (Entity::isDestroyed()) {
		//isMarkedForRemoval = true;
		//return;
	}

	if (suppressInteracting == true) {
		suppressInteracting = false;
	}
	else {
		isInteracting = false;
	}

	Attacker::update(dt, Commands, *this);

	WeaponWielder::update(dt, Commands, *this);

	Actionable::update(dt, Commands, *this);

	Platformer::updateCurrent(dt, Commands);
};