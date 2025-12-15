#include "ChangeAnimation.h"
#include "Animatable.h"

ChangeAnimation::ChangeAnimation(std::string animation)
: animation(animation)
, Action(Action::RunOnce)
{
}

void ChangeAnimation::update(sf::Time dt, CommandQueue& Commands, SceneNode& target)
{
	Animatable* animatable = dynamic_cast<Animatable*>(&target);
	
	animatable->setAnimation(animation);
	
};

bool ChangeAnimation::isFinnished() {
	return true;
};

void ChangeAnimation::reset() {
}
