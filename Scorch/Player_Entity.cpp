#include "Player_Entity.h"
#include "Utility.hpp"

#include "Greatsword.h"
#include "Slash.h"

Player_Entity* Player_Entity::instance = nullptr;

Player_Entity::Player_Entity(const TextureHolder& resources, json data)
: PlatformerMovementSuite()
, Entity(50)
, Animatable(resources, data["Animatable"])
, mPlayerState(grounded)
, isAttacking(false)
, isInteracting(false)
{
	// push starting weapon
	//WeaponWielder::pushWeapon(new Greatsword(resources, Category::Enemy));
	instance = this;
}

std::vector<unsigned int> Player_Entity::getCategory() const {
	std::vector<unsigned int> i(PlatformerMovementSuite::getCategory());
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
}

bool Player_Entity::isDestroyed() const
{
	return Entity::isDestroyed();
}

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

Player_Entity::playerState Player_Entity::getPlayerState() const
{
	return mPlayerState;
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

	PlatformerMovementSuite::updateCurrent(dt, Commands);

};