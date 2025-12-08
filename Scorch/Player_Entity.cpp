#include "Player_Entity.h"
#include "Utility.hpp"

#include "Greatsword.h"
#include "Slash.h"

Player_Entity* Player_Entity::instance = nullptr;

Player_Entity::Player_Entity(const TextureHolder& resources)
: Platformer(50)
, isMarkedForRemoval(false)
, isAttacking(false)
, isInteracting(false)
, suppressInteracting(false)
, mSprite(resources.get(Textures::Player))
{
	//centerOrigin(mSprite);
	
	// Example: create a simple Animation and register it with ChangeableAnimation.
	// Adjust frame size, frame count and duration to match your sprite sheet.
	Animation idleAnim(resources.get("PlayerAni"));
	idleAnim.setFrameSize(sf::Vector2i(80,80));    // example frame size
	idleAnim.setNumFrames(3);                     // example frame count
	idleAnim.setDuration(sf::seconds(0.6f));
	idleAnim.setRepeating(true);
	idleAnim.setCentered(true);

	mAnimations.addAnimation("Idle", std::move(idleAnim));
	mAnimations.setDefaultAnimation("Idle");
	mAnimations.setAnimation("Idle", sf::seconds(1.8f));

	// push starting weapon
	WeaponWielder::pushWeapon(new Greatsword(resources, Category::Enemy));
	instance = this;
}

Player_Entity::Player_Entity(const TextureHolder& resources, json data)
: Platformer(50)
, Animatable(resources, data["Animatable"])
, isMarkedForRemoval(false)
, isAttacking(false)
, isInteracting(false)
, suppressInteracting(false)
, mSprite(resources.get(Textures::Player))
{


	// push starting weapon
	WeaponWielder::pushWeapon(new Greatsword(resources, Category::Enemy));
	instance = this;
}

std::vector<unsigned int> Player_Entity::getCategory() const {
	std::vector<unsigned int> i(Platformer::getCategory());
	i.push_back(Category::Player);
	return i;
};

sf::FloatRect Player_Entity::getBoundingRect() const {
	//return getWorldTransform().transformRect(/*getGlobalBounds()*/mSprite.getGlobalBounds());
	return getWorldTransform().transformRect(getGlobalBounds());
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
	//target.draw(mSprite, states);

	target.draw(mAnimations, states);
}

void Player_Entity::updateCurrent(sf::Time dt, CommandQueue& Commands) {
	if (Entity::isDestroyed()) {
		isMarkedForRemoval = true;
		return;
	}

	if (suppressInteracting == true) {
		suppressInteracting = false;
	}
	else {
		isInteracting = false;
	}

	Animatable::update(dt);

	Attacker::update(dt, Commands, *this);

	WeaponWielder::update(dt, Commands, *this);

	Actionable::update(dt, Commands, *this);

	Platformer::updateCurrent(dt, Commands);
};