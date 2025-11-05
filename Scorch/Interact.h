#pragma once

#include "Actions.h"

class Interact : public Action
{
public:
	Interact();
	virtual void update(sf::Time dt, CommandQueue& Commands, SceneNode& target);
	virtual bool isFinnished();
	virtual void reset();
};

