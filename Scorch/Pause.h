#pragma once

#include "Action.h"
#include "Entity.hpp"

class Pause : public Action
{
public:
	Pause(Action::Type type, sf::Time duration);
	virtual void update(sf::Time dt, CommandQueue& Commands, SceneNode& target);
	virtual bool isFinnished();
	virtual void reset();

private:
	sf::Time mDuration;
	sf::Time mTime;
};

