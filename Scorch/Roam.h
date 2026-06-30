#pragma once

#include "Action.h"
#include <SFML/System.hpp>
#include <random>

class Roam : public Action
{
public:
	Roam(Action::Type type, double rangeL, double rangeR, double playerRange = -1);
	virtual void update(sf::Time dt, CommandQueue& Commands, SceneNode& target);
	virtual bool isFinnished();
	virtual void reset();

private:
	double rangeL;
	double rangeR;
	bool movingRight;
	double playerRange;
	bool isFinished;

	// Wandering state
	double originX;
	bool originSet;

	// Movement / pause state
	bool paused;
	double currentTargetX;
	sf::Time timeSinceActionChange; // time in current phase
	sf::Time actionInterval;        // duration of current phase (move or pause)

	// RNG for intervals and target selection
	std::mt19937 rng;
};