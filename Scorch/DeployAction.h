#pragma once

#include "WorldAction.h"
#include "Action.h"

#include "Categories.hpp"

class DeployAction : public WorldAction
{
public:
	DeployAction(Category::Type target, Action* actionToDeploy);
	virtual void update(sf::Time dt, CommandQueue& Commands, World& target);
	virtual bool isFinnished();

private:
	Category::Type mTarget;
	Action* mActionToDeploy;
};

