#include "ChangeAnimation.h"
#include "Animatable.h"
#include "Utility.hpp"

ChangeAnimation::ChangeAnimation(std::string animation)
: animation(animation)
, Action(Action::RunOnce)
, mTarget(nullptr)
{
}

void ChangeAnimation::update(sf::Time dt, CommandQueue& Commands, SceneNode& target)
{
	if (mTarget == nullptr) {
		if (Animatable* castedPtr = dynamic_cast<Animatable*>(&target)) {
			mTarget = castedPtr;
		}
		//mTarget = safeCast<Animatable*, SceneNode*>(&target);
	}
	mTarget->setAnimation(animation);
	
};

bool ChangeAnimation::isFinnished() {
	return true;
};

void ChangeAnimation::reset() {
}
