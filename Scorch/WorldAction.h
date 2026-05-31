#pragma once

#include "CommandQueue.hpp"
#include "SceneNode.hpp"

class WorldAction
{
public:
	WorldAction();
	virtual void update(sf::Time dt, CommandQueue& Commands, World& target);
	virtual bool isFinnished();
};

