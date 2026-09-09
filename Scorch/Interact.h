#pragma once

#include "Action.h"
#include "Player_Entity.h"

class Interact : public Action
{
public:
	Interact();
	virtual void update(sf::Time dt, CommandQueue& Commands, SceneNode& target);
	virtual bool isFinnished();
	virtual void reset();

private:
	Player_Entity* mTarget;
};

