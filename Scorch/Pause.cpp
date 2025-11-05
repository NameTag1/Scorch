#include "Pause.h"

Pause::Pause(sf::Time duration)
: mDurration(duration)
, mTime(sf::seconds(0))
, Action(Persistent)
{
}

void Pause::update(sf::Time dt, CommandQueue& Commands, SceneNode& target)
{
	mTime += dt;
};

bool Pause::isFinnished() {
	if (mTime >= mDurration) {
		return true;
	}
	return false;
};

void Pause::reset() {
	mTime = sf::seconds(0);
}