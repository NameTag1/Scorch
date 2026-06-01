#include "Player_Entity.h"
#include "Utility.hpp"

#include "Greatsword.h"
#include "Slash.h"

Player_Entity* Player_Entity::instance = nullptr;

Player_Entity::Player_Entity(const TextureHolder& resources, json data)
: Platformer(50)
, Animatable(resources, data["Animatable"])
, isAttacking(false)
, isInteracting(false)
{
	// push starting weapon
	//WeaponWielder::pushWeapon(new Greatsword(resources, Category::Enemy));
	instance = this;
}

std::vector<unsigned int> Player_Entity::getCategory() const {
	std::vector<unsigned int> i(Platformer::getCategory());
	i.push_back(Category::Player);
	return i;
};

sf::FloatRect Player_Entity::getBoundingRect() const {
	//return getWorldTransform().transformRect(/*getGlobalBounds()*/mSprite.getGlobalBounds());
	return getWorldTransform().transformRect(Animatable::getGlobalBounds());
};

bool Player_Entity::isMarkedForRemoval() const {
	//return Entity::isMarkedForRemoval();
	return false; //Player is never removed, only killed (destroyed)
};

bool Player_Entity::getInteracting() {
	return isInteracting;
};

void Player_Entity::setInteracting(bool interacting) {
	isInteracting = interacting;
}

Player_Entity* Player_Entity::getInstance() {
	return instance;
}

void Player_Entity::resetInstance()
{
	instance = nullptr;
}

void Player_Entity::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(mAnimations, states);
}

void Player_Entity::updateCurrent(sf::Time dt, CommandQueue& Commands) {
	if (Entity::isDestroyed()) {
		return;
	}

	isInteracting = false; //Every tic, stop interacting.

	Animatable::update(dt);

	Attacker::update(dt, Commands, *this);

	WeaponWielder::update(dt, Commands, *this);

	Actionable::update(dt, Commands, *this);

	Platformer::updateCurrent(dt, Commands);
};