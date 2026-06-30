#include "Move.h"
#include "Platformer.h"

Move::Move(bool running, bool left)
: mRunning(running)
, mLeft(left)
, Action(Live)
{
}

void Move::update(sf::Time dt, CommandQueue& Commands, SceneNode& target)
{
	Platformer* platformer = dynamic_cast<Platformer*>(&target);
	platformer->move(mRunning, mLeft);
}

bool Move::isFinnished()
{
	return true;
}

void Move::reset()
{
}
