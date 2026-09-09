#pragma once

#include "Action.h"

#include "Platformer.h"

class FleePlayer : public Action
{
public:
	FleePlayer(int distance);
	virtual void update(sf::Time dt, CommandQueue& Commands, SceneNode& target);
	virtual bool isFinnished();
	virtual void reset();

private:
	int distance;
	sf::Vector2f mLastPos;

	Platformer* mTarget;
};


