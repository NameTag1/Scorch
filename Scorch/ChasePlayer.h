#pragma once

#include "Actions.h"

class ChasePlayer : public Action
{
public:
	ChasePlayer(int distance);
	virtual void update(sf::Time dt, CommandQueue& Commands, SceneNode& target);
	virtual bool isFinnished();
	virtual void reset();

private:
	int distance;
	sf::Vector2f mLastPos;
};

