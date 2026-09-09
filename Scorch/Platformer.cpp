#include "Platformer.h"
#include "Utility.hpp"
#include <cmath>
#include "Logger.h"
#include "World.hpp"

Platformer::Platformer()
: onPlatform(false)
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
		
		//Static and Kinetic Friction
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

std::vector<unsigned int> Platformer::getCategory() const
{
	std::vector<unsigned int> i(Movable::getCategory());
	i.push_back(Category::Platformer);
	return i;
}

bool Platformer::getOnPlatform() {
	return onPlatform;
}

void Platformer::updateCurrent(sf::Time dt, CommandQueue& Commands) {
	onPlatform = false; //Handle Collisions in World will change if on platform

	Movable::updateCurrent(dt, Commands);
};

sf::FloatRect Platformer::calculateOverlap(sf::FloatRect rect1, sf::FloatRect rect2) {
	float overlapX = std::max(0.f, std::min(rect1.getPosition().x + rect1.width, rect2.getPosition().x + rect2.width) - std::max(rect1.getPosition().x, rect2.getPosition().x));
	float overlapY = std::max(0.f, std::min(rect1.getPosition().y + rect1.height, rect2.getPosition().y + rect2.height) - std::max(rect1.getPosition().y, rect2.getPosition().y));
	return sf::FloatRect(0, 0, overlapX, overlapY);
}
