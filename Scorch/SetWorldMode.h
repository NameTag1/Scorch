#pragma once

#include "WorldAction.h"
#include "World.hpp"

class SetWorldMode : public WorldAction
{
public:
	SetWorldMode(World::World_Mode mode);
	virtual void update(sf::Time dt, CommandQueue& Commands, World& target);
	virtual bool isFinnished();

private:
	World::World_Mode mMode;
};

