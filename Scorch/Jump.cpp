#include "Jump.h"
#include <iostream>

Jump::Jump()
: mJumped(false)
, Action(Action::RunOnce)
{
}

void Jump::update(sf::Time dt, CommandQueue& Commands, SceneNode& target)
{
	Platformer *platformer = dynamic_cast<Platformer*>(&target);
	if (platformer->jump()) {
		mJumped = true;
	};
};

bool Jump::isFinnished() {
	return true;
};

void Jump::reset() {
	mJumped = false;
}