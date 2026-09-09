#include "Dash.h"

#include "Utility.hpp"

Dash::Dash()
: Action(Action::RunOnce)
, mTarget(nullptr)
{
}

void Dash::update(sf::Time dt, CommandQueue& Commands, SceneNode& target)
{
	if (mTarget == nullptr) {
		if (PlatformerMovementSuite* castedPtr = dynamic_cast<PlatformerMovementSuite*>(&target)) {
			mTarget = castedPtr;
		}
		//mTarget = safeCast<PlatformerMovementSuite*, SceneNode*>(&target);
	}

	if(mTarget->lastKnownAcceleration().x > 0) {
		mTarget->dash(false); // Dash to the right
	}
	else if(mTarget->lastKnownAcceleration().x < 0) {
		mTarget->dash(true); // Dash to the left
	}
};

bool Dash::isFinnished() {
	return true;
};

void Dash::reset() {
}