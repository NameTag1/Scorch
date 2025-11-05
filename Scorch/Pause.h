#pragma once

#include "Actions.h"
#include "Entity.hpp"

class Pause : public Action
{
public:
	Pause(sf::Time duration);
	virtual void update(sf::Time dt, CommandQueue& Commands, SceneNode& target);
	virtual bool isFinnished();
	virtual void reset();

private:
	sf::Time mDurration;
	sf::Time mTime;
};

