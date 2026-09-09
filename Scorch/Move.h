#pragma once

#include "Action.h"
#include "PlatformerMovementSuite.h"

class Move : public Action
{
public:
	Move(bool running, bool left);
	virtual void update(sf::Time dt, CommandQueue& Commands, SceneNode& target);
	virtual bool isFinnished();
	virtual void reset();

private:
	bool mRunning;
	bool mLeft;

	PlatformerMovementSuite* mTarget;
};

