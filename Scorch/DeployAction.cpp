#include "DeployAction.h"

#include "World.hpp"

DeployAction::DeployAction(Category::Type target, Action* actionToDeploy)
: mTarget(target)
, mActionToDeploy(actionToDeploy)
{
}

void DeployAction::update(sf::Time dt, CommandQueue& Commands, World& target)
{
	target.deployActionToChildren(mTarget, mActionToDeploy);
}

bool DeployAction::isFinnished()
{
	return true;
}
