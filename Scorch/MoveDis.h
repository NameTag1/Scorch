#pragma once

#include "Actions.h"
#include "Entity.hpp"

class MoveDis : public Action
{
public:
	MoveDis(int distance);
	virtual void update(sf::Time dt, CommandQueue& Commands, SceneNode& target);
	virtual bool isFinnished();
	virtual void reset();

private:
	bool mLeft;
	sf::Vector2f mStart;
	int mDistance;
	int mDistanceTraveled;
};

