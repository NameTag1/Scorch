#include "Roam.h"
#include "World.hpp"
#include "Platformer.h"
#include "Player_Entity.h"
#include <random>
#include <cmath>

Roam::Roam(Action::Type type, double rangeL, double rangeR, double playerRange)
	: Action(type)
	, rangeL(rangeL)
	, rangeR(rangeR)
	, movingRight(true)
	, playerRange(playerRange)
	, isFinished(false)
	, originX(0.0)
	, originSet(false)
	, paused(false)
	, currentTargetX(0.0)
	, timeSinceActionChange(sf::Time::Zero)
	, actionInterval(sf::seconds(1.f))
{
	std::random_device rd;
	rng.seed(rd());
}

void Roam::update(sf::Time dt, CommandQueue& Commands, SceneNode& target)
{
	Platformer* platformer = dynamic_cast<Platformer*>(&target);
	if (!platformer) return;

	// Initialize origin and initial phase on first update
	if (!originSet) {
		originX = platformer->getWorldPosition().x;
		originSet = true;

		std::uniform_real_distribution<double> intervalDist(0.5, 3.0);
		paused = (rng() & 1) != 0; // random start: paused or moving

		if (paused) {
			actionInterval = sf::seconds(static_cast<float>(intervalDist(rng)));
		}
		else {
			// pick initial movement target and interval
			std::uniform_real_distribution<double> targetDist(originX - rangeL, originX + rangeR);
			currentTargetX = targetDist(rng);
			actionInterval = sf::seconds(static_cast<float>(intervalDist(rng)));
			movingRight = (currentTargetX > platformer->getWorldPosition().x);
		}

		timeSinceActionChange = sf::Time::Zero;
	}

	// Finish if player is within playerRange (if enabled)
	if (playerRange != -1) {
		sf::Vector2f playerPos = Player_Entity::getInstance()->getWorldPosition();
		if (std::abs(playerPos.x - platformer->getWorldPosition().x) < playerRange) {
			isFinished = true;
		}
	}

	// If finished, do not roam
	if (isFinnished()) return;

	// Accumulate time
	timeSinceActionChange += dt;

	// Distributions for choosing intervals/targets
	std::uniform_real_distribution<double> intervalDist(0.5, 3.0);
	std::uniform_real_distribution<double> targetDist(originX - rangeL, originX + rangeR);

	if (paused) {
		// Currently paused: do not call move
		if (timeSinceActionChange >= actionInterval) {
			// Switch to movement phase
			paused = false;
			currentTargetX = targetDist(rng);
			actionInterval = sf::seconds(static_cast<float>(intervalDist(rng)));
			timeSinceActionChange = sf::Time::Zero;
			movingRight = (currentTargetX > platformer->getWorldPosition().x);
		}
	}
	else {
		// Movement phase: move toward currentTargetX
		double currentX = platformer->getWorldPosition().x;
		// If reached target (within small epsilon) or time expired, enter pause
		const double reachEps = 1.0;
		if (std::abs(currentTargetX - currentX) <= reachEps || timeSinceActionChange >= actionInterval) {
			paused = true;
			actionInterval = sf::seconds(static_cast<float>(intervalDist(rng))); // pause length similar to move length
			timeSinceActionChange = sf::Time::Zero;
		}
		else {
			// Enforce bounds: reverse target direction if outside allowed range
			if (currentX <= originX - rangeL) {
				movingRight = true;
			}
			else if (currentX >= originX + rangeR) {
				movingRight = false;
			}
			// Move using Platformer API (expects left boolean)
			bool left = !movingRight;
			platformer->move(false, left);
		}
	}
}

bool Roam::isFinnished()
{
	return isFinished;
}

void Roam::reset()
{
	isFinished = false;
	originSet = false;
	timeSinceActionChange = sf::Time::Zero;
	paused = false;
}