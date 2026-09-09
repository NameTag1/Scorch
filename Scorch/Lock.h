#pragma once

#include "Player_Entity.h"

class Lock : public Action
{
public:
	Lock(bool locked);

	virtual void update(sf::Time dt, CommandQueue& Commands, SceneNode& target);
	virtual bool isFinnished();
	virtual void reset();

private:
	bool mLock;

	Player_Entity* mTarget;
};

