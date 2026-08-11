#include "Platformer.h"
#include "Utility.hpp"
#include <cmath>
#include "Logger.h"
#include "World.hpp"

Platformer::Platformer(int health)
: onPlatform(false)
, brakingEnabled(true)
, Entity(health)
, mAcceleration(30.f) //meters per second^2
, mMaxSpeed(6.5f) //meters per second
, mWalkFactor(0.3f)
, mDashPower(1000.f) //In N
, mJumpPower(500.f) //In N
, mIntendedForceX(0.f)
, mFallControl(0.1f)
{
}

void Platformer::adust_for_platform(Platform& p) {
	sf::Vector2f unitV = unitVector(getVelocity());

	sf::FloatRect playerRect = getBoundingRect();
	sf::FloatRect platformRect = p.getBoundingRect();
	sf::Vector2f playerPos = getPosition();
	sf::Vector2f platformPos = p.getPosition();
	sf::FloatRect Overlap = calculateOverlap(playerRect, platformRect);
	
	//Adjust player pos for platforms
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
	
	// Friction Handling
	if (onPlatform) {
		float vx = getVelocity().x;
		// Use world's gravity to compute normal force
		float gravity = 9.81f;
		if (World::getInstance()) gravity = (float)World::getInstance()->getGravity();
		float normal = getWeight() * gravity;
		float sMax = p.getSFriction() * normal; // max static friction (N)
		float kForce = p.getKFriction() * normal; // kinetic friction force magnitude (N)

		const float velThreshold = 0.2f; // m/s: below this we consider the player stopped

		// Player IS attempting to move.
		if (mIntendedForceX != 0.f) {
			if (std::fabs(vx) < velThreshold && std::fabs(mIntendedForceX) <= sMax) {
				setVelocity(0, getVelocity().y);
			}
			else {
				// moving: apply kinetic friction opposing motion
				if (vx > 0) {
					Movable::applyForce(-kForce, 0);

					//BRAKING
					if (brakingEnabled && mIntendedForceX < 0) {
						Movable::applyForce(-mAcceleration * getWeight(), 0);
					}
				}
				else if (vx < 0) {
					Movable::applyForce(kForce, 0);

					//BRAKING
					if (brakingEnabled && mIntendedForceX < 0) {
						Movable::applyForce(mAcceleration * getWeight(), 0);
					}
				}
			}
		}
		// Player IS NOT attempting to move.
		else {
			// No input: kinetic friction slows player to a stop
			if (std::fabs(vx) < velThreshold) {
				setVelocity(0, getVelocity().y);
			}
			else {
				if (vx > 0) {
					Movable::applyForce(-kForce, 0);
				}
				else if (vx < 0) {
					Movable::applyForce(kForce, 0);
				}
			}
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
		Entity::applyInstantaneousForce(0, -mJumpPower);
		onPlatform = false;
		return true;
	}
	else {
		return false;
	}
}

bool Platformer::dash(bool left) {
	if (Movable::lastKnownAcceleration().x > 0) {
		Movable::applyInstantaneousForce(mDashPower, 0);
		Logger::Instance->LogData(Logger::Action, "Dashed");
	}
	else if (Movable::lastKnownAcceleration().x < 0) {
		Movable::applyInstantaneousForce(-mDashPower, 0);
		Logger::Instance->LogData(Logger::Action, "Dashed");
	}
	else {
		Logger::Instance->LogData(Logger::Action, "FAIL");
		return false;
	}
	return true;
};

void Platformer::move(bool running, bool left) {
	float appliedForce = (running) ? mAcceleration * getWeight() : mAcceleration * mWalkFactor * getWeight();

	if (!onPlatform/* && mPlatformState != falling*/) {
		appliedForce *= mFallControl; // Reduce horizontal control while falling
	}

	float vx = Entity::getVelocity().x;
	// Determine intended horizontal direction: -1 for left, +1 for right
	int intendedDir = (left) ? -1 : 1;

	// Record intended force for friction/static friction checks
	mIntendedForceX = (left ? -appliedForce : appliedForce);

	// Only apply force if we haven't reached the signed max speed in the intended direction.
	if (left && Movable::getVelocity().x > -mMaxSpeed) {	
		Entity::applyForce(mIntendedForceX, 0);
	}
	else if (!left && Movable::getVelocity().x < mMaxSpeed) {
		Entity::applyForce(mIntendedForceX, 0);
	}
}

void Platformer::setSpeed(float speed)
{
	mMaxSpeed = speed;
}

void Platformer::braking(bool isBraking)
{
	brakingEnabled = isBraking;
}

void Platformer::updateCurrent(sf::Time dt, CommandQueue& Commands) {
	onPlatform = false; //Handle Collisions in World will change if on platform
	// Reset intended input force; move() will set this if input is present this frame
	mIntendedForceX = 0.f;
	Entity::updateCurrent(dt, Commands);
};

sf::FloatRect Platformer::calculateOverlap(sf::FloatRect rect1, sf::FloatRect rect2) {
	float overlapX = std::max(0.f, std::min(rect1.getPosition().x + rect1.width, rect2.getPosition().x + rect2.width) - std::max(rect1.getPosition().x, rect2.getPosition().x));
	float overlapY = std::max(0.f, std::min(rect1.getPosition().y + rect1.height, rect2.getPosition().y + rect2.height) - std::max(rect1.getPosition().y, rect2.getPosition().y));
	return sf::FloatRect(0, 0, overlapX, overlapY);
}
