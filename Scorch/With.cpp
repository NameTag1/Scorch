#include "With.h"

With::With(Action* Action1, Action* Action2)
: Action1(Action1)
, Action2(Action2)
, Action(Persistent)
{
}

With::With(Action* Action1, Action* Action2, Action::Type ActionType)
: Action1(Action1)
, Action2(Action2)
, Action(ActionType)
{
}

void With::update(sf::Time dt, CommandQueue& Commands, SceneNode& target)
{
	Action1->update(dt, Commands, target);
	Action2->update(dt, Commands, target);
}

bool With::isFinnished()
{
	return (Action1->isFinnished() && Action2->isFinnished());
}

void With::reset()
{
	Action1->reset();
	Action2->reset();
}




