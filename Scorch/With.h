#pragma once

#include "Actions.h"


//Run two actions at the same time. Finished when both are done.
class With : public Action
{
public:
	With(Action* Action1, Action* Action2);
	With(Action* Action1, Action* Action2, Action::Type ActionType);
	virtual void update(sf::Time dt, CommandQueue& Commands, SceneNode& target);
	virtual bool isFinnished();
	virtual void reset();

private:
	Action* Action1;
	Action* Action2;
};

