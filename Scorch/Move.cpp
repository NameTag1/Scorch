#include "Move.h"

Move::Move(bool left)
: mLeft(left)
, Action(Live)
{
}

void Move::update(sf::Time dt, CommandQueue& Commands, SceneNode& target)
{
	Platformer* platformer = dynamic_cast<Platformer*>(&target);
	platformer->move(mLeft);
}

bool Move::isFinnished()
{
	return true;
}

void Move::reset()
{
}
