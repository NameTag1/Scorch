#pragma once

#include "Action.h"

#include "PlatformerMovementSuite.h"

class Dash : public Action
{
public:
	Dash();
	virtual void update(sf::Time dt, CommandQueue& Commands, SceneNode& target);
	virtual bool isFinnished();
	virtual void reset();

private:
	PlatformerMovementSuite* mTarget;
};


