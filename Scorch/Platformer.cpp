#include "Platformer.h"
#include "Utility.hpp"
#include <iostream>

Platformer::Platformer(int health) 
: onPlatform(false) 
, Entity(health)
, maxMoveSpeed(9999)
, mSpeed(100)
, mJumpPower(1400)
{
}

void Platformer::adust_for_platform(Platform& p) {
	sf::Vector2f unitV = unitVector(getVelocity());

	sf::FloatRect playerRect = getBoundingRect();
	sf::FloatRect platformRect = p.getBoundingRect();
	sf::Vector2f playerPos = getPosition();
	sf::Vector2f platformPos = p.getPosition();
	sf::FloatRect Overlap = calculateOverlap(playerRect, platformRect);
	
	if (Overlap.size.x < Overlap.size.y) {
		if (playerPos.x < platformPos.x) {
			setPosition(platformPos.x - playerRect.size.x + playerRect.size.x / 2, playerPos.y);
			if (getVelocity().x > 0) {
				setVelocity(0, getVelocity().y);
			}
		}
		else {
			setPosition(platformPos.x + platformRect.size.x + playerRect.size.x / 2, playerPos.y);
			if (getVelocity().x < 0) {
				setVelocity(0, getVelocity().y);
			}
		}
	} else {
		if (playerPos.y < platformPos.y) {
			setPosition(playerPos.x, platformPos.y - playerRect.size.y + playerRect.size.y / 2);
			if (getVelocity().y > 0) {
				setVelocity(getVelocity().x, 0);
				onPlatform = true;
			}
		}
		else {
			setPosition(playerPos.x, platformPos.y + platformRect.size.y + playerRect.size.y / 2);
			if (getVelocity().y < 0) {
				setVelocity(getVelocity().x, 0);
			}
		}
	}

	if (onPlatform && getVelocity().x) {
		if( -p.getFriction() < getVelocity().x && getVelocity().x < p.getFriction()){
		}
		else if (getVelocity().x > 0) {
			setVelocity(getVelocity().x - p.getFriction(), getVelocity().y);
		}
		else {
			setVelocity(getVelocity().x + p.getFriction(), getVelocity().y);
		}
	}
}
std::vector<unsigned int> Platformer::getCategory() const
{
	std::vector<unsigned int> i(Entity::getCategory());
	i.push_back(Category::Platformer);
	return i;
}
;

bool Platformer::getOnPlatform() {
	return onPlatform;
}

bool Platformer::jump() {
	if (getOnPlatform() && Entity::getVelocity().y >= 0) {
		Entity::setVelocity(Entity::getVelocity().x, 0);
		Entity::accelerate(0, -mJumpPower);
		onPlatform = false;
		return true;
	}
	else {
		return false;
	}
}

void Platformer::move(bool left) {
	if (left) {
		if (Entity::getVelocity().x - mSpeed > -maxMoveSpeed) {
			Entity::accelerate(-mSpeed, 0);
		}
		else {
			Entity::setVelocity(-maxMoveSpeed, getVelocity().y);
		}
	}
	else {
		if (Entity::getVelocity().x + mSpeed < maxMoveSpeed) {
			Entity::accelerate(mSpeed, 0);
		}
		else {
			Entity::setVelocity(maxMoveSpeed, getVelocity().y);
		}
	}
}

void Platformer::setSpeed(double speed)
{
	mSpeed = speed;
}

void Platformer::updateCurrent(sf::Time dt, CommandQueue& Commands) {
	onPlatform = false; //Handle Collisions in World will change if on platform
	Entity::updateCurrent(dt, Commands);
};

sf::FloatRect Platformer::calculateOverlap(sf::FloatRect rect1, sf::FloatRect rect2) {
	float overlapX = std::max(0.f, std::min(rect1.position.x + rect1.size.x, rect2.position.x + rect2.size.x) - std::max(rect1.position.x, rect2.position.x));
	float overlapY = std::max(0.f, std::min(rect1.position.y + rect1.size.y, rect2.position.y + rect2.size.y) - std::max(rect1.position.y, rect2.position.y));
	return sf::FloatRect({ 0, 0 }, { overlapX, overlapY });
}
