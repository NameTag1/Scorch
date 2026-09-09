#include "Pause.h"

Pause::Pause(Action::Type type, sf::Time duration)
: mDuration(duration)
, mTime(sf::seconds(0))
, Action(type)
{
}

void Pause::update(sf::Time dt, CommandQueue& Commands, SceneNode& target)
{
	mTime += dt;
};

bool Pause::isFinnished() {
	if (mTime >= mDuration) {
		return true;
	}
	return false;
};

void Pause::reset() {
	mTime = sf::seconds(0);
}