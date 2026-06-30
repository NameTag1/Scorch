#include "Platformer.h"
#include "Utility.hpp"
#include <cmath>

Platformer::Platformer(int health) 
: onPlatform(false) 
, Entity(health)
, maxMoveSpeed(9999.f)
, mRunSpeed(150.f)
, mWalkFactor(0.3f)
, mJumpPower(1400)
, mPlatformState(grounded)
{
}

void Platformer::adust_for_platform(Platform& p) {
	sf::Vector2f unitV = unitVector(getVelocity());

	sf::FloatRect playerRect = getBoundingRect();
	sf::FloatRect platformRect = p.getBoundingRect();
	sf::Vector2f playerPos = getPosition();
	sf::Vector2f platformPos = p.getPosition();
	sf::FloatRect Overlap = calculateOverlap(playerRect, platformRect);
	
	if (Overlap.width < Overlap.height) {
		if (playerPos.x < platformPos.x) {
			setPosition(platformPos.x - playerRect.width + playerRect.width / 2, getPosition().y);
			if (getVelocity().x > 0) {
				setVelocity(0, getVelocity().y);
			}
		}
		else {
			setPosition(platformPos.x + platformRect.width + playerRect.width / 2, getPosition().y);
			if (getVelocity().x < 0) {
				setVelocity(0, getVelocity().y);
			}
		}
	} else {
		if (playerPos.y < platformPos.y) {
			setPosition(getPosition().x, platformPos.y - playerRect.height + playerRect.height / 2);
			if (getVelocity().y > 0) {
				setVelocity(getVelocity().x, 0);
				onPlatform = true;
			}
		}
		else {
			setPosition(getPosition().x, platformPos.y + platformRect.height + playerRect.height / 2);
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

bool Platformer::getOnPlatform() {
	return onPlatform;
}

bool Platformer::jump() {
	if (getOnPlatform() && Entity::getVelocity().y >= 0) {
		Entity::setVelocity(Entity::getVelocity().x, 0);
		Entity::accelerate(0, -mJumpPower);
		onPlatform = false;
		mPlatformState = jumping;
		return true;
	}
	else {
		return false;
	}
}

void Platformer::move(bool running, bool left) {
	if (!onPlatform) {
		return;
	}

	double speed = (running) ? mRunSpeed : mRunSpeed*mWalkFactor;
	float vx = Entity::getVelocity().x;
	// Determine intended horizontal direction: -1 for left, +1 for right
	int intendedDir = (left) ? -1 : 1;

	// If applying acceleration opposite current motion, we're drifting
	if ((vx > 0 && intendedDir < 0) || (vx < 0 && intendedDir > 0)) {
		mPlatformState = drifting;
	}
	else if (running) {
		mPlatformState = platformState::running;
	}
	else {
		mPlatformState = walking;
	}

	if (left) {
		if (Entity::getVelocity().x - speed > -maxMoveSpeed) {
			Entity::accelerate(-float(speed), 0);
		}
		else {
			Entity::setVelocity(-maxMoveSpeed, getVelocity().y);
		}
	}
	else {
		if (Entity::getVelocity().x + speed < maxMoveSpeed) {
			Entity::accelerate(float(speed), 0);
		}
		else {
			Entity::setVelocity(maxMoveSpeed, getVelocity().y);
		}
	}
}

void Platformer::setSpeed(float speed)
{
	mRunSpeed = speed;
}

void Platformer::updateCurrent(sf::Time dt, CommandQueue& Commands) {
	onPlatform = false; //Handle Collisions in World will change if on platform
	Entity::updateCurrent(dt, Commands);
	// Update platform state based on whether we're on a platform and our velocity
	if (onPlatform) {
		float vx = getVelocity().x;
		// Standing still on ground
		if (std::abs(vx) < 0.001f) {
			mPlatformState = grounded;
		}
		// if already set to running/walking/drifting by move(), keep it
		// otherwise default to walking when moving slowly, running when fast
		else {
			if (mPlatformState == grounded || mPlatformState == jumping || mPlatformState == falling) {
				// choose by speed magnitude
				if (std::abs(vx) > mRunSpeed * 0.5f) {
					mPlatformState = running;
				}
				else {
					mPlatformState = walking;
				}
			}
		}
	}
	else {
		// In air: determine jump vs fall by vertical velocity
		float vy = getVelocity().y;
		if (vy < 0) {
			mPlatformState = jumping;
		}
		else {
			mPlatformState = falling;
		}
	}
};

sf::FloatRect Platformer::calculateOverlap(sf::FloatRect rect1, sf::FloatRect rect2) {
	float overlapX = std::max(0.f, std::min(rect1.getPosition().x + rect1.width, rect2.getPosition().x + rect2.width) - std::max(rect1.getPosition().x, rect2.getPosition().x));
	float overlapY = std::max(0.f, std::min(rect1.getPosition().y + rect1.height, rect2.getPosition().y + rect2.height) - std::max(rect1.getPosition().y, rect2.getPosition().y));
	return sf::FloatRect(0, 0, overlapX, overlapY);
}
