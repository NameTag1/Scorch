#pragma once

#include "Actions.h"
#include "Entity.hpp"

class Lock : public Action
{
public:
	Lock(bool locked);
	virtual void update(sf::Time dt, CommandQueue& Commands, SceneNode& target);
	virtual bool isFinnished();
	virtual void reset();

private:
	bool mLock;
};

