#pragma once

#include "Action.h"

class Move : public Action
{
public:
	Move(bool left);
	virtual void update(sf::Time dt, CommandQueue& Commands, SceneNode& target);
	virtual bool isFinnished();
	virtual void reset();

private:
	bool mLeft;
};

