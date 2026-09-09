#include "Move.h"

#include "Utility.hpp"

Move::Move(bool running, bool left)
: mRunning(running)
, mLeft(left)
, Action(Live)
{
}

void Move::update(sf::Time dt, CommandQueue& Commands, SceneNode& target)
{
	if (mTarget == nullptr) {
		if (PlatformerMovementSuite* castedPtr = dynamic_cast<PlatformerMovementSuite*>(&target)) {
			mTarget = castedPtr;
		}
		//mTarget = safeCast<PlatformerMovementSuite*, SceneNode*>(&target);
	}
	mTarget->move(mRunning, mLeft);
}

bool Move::isFinnished()
{
	return true;
}

void Move::reset()
{
}
