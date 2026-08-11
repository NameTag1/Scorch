#pragma once

#include "Action.h"
#include "Entity.hpp"
#include "Platformer.h"

class Dash : public Action
{
public:
	Dash();
	virtual void update(sf::Time dt, CommandQueue& Commands, SceneNode& target);
	virtual bool isFinnished();
	virtual void reset();
};


