#include "Jump.h"

#include "Utility.hpp"

Jump::Jump()
: mJumped(false)
, Action(Action::RunOnce)
{
}

void Jump::update(sf::Time dt, CommandQueue& Commands, SceneNode& target)
{
	if (mTarget == nullptr) {
		if (PlatformerMovementSuite* castedPtr = dynamic_cast<PlatformerMovementSuite*>(&target)) {
			mTarget = castedPtr;
		}
		// mTarget = safeCast<PlatformerMovementSuite*, SceneNode*>(&target);
	}
	if (mTarget->jump()) {
		mJumped = true;
	};
};

bool Jump::isFinnished() {
	return true;
};

void Jump::reset() {
	mJumped = false;
}