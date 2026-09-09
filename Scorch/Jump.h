#pragma once

#include "Action.h"

#include "PlatformerMovementSuite.h"

class Jump : public Action
{
public:
	Jump();
	virtual void update(sf::Time dt, CommandQueue& Commands, SceneNode& target);
	virtual bool isFinnished();
	virtual void reset();

private:
	bool mJumped;

	PlatformerMovementSuite* mTarget;
};

