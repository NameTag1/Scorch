#pragma once

#include "Actions.h"

class ChangeAnimation : public Action
{
public:
	ChangeAnimation(std::string animation);
	virtual void update(sf::Time dt, CommandQueue& Commands, SceneNode& target);
	virtual bool isFinnished();
	virtual void reset();

private:
	std::string animation;
};

