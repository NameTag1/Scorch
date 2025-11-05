#include "Lock.h"
#include "Actionable.h"

Lock::Lock(bool mLocked)
: mLock(mLocked)
, Action(Action::RunOnce)
{
}

void Lock::update(sf::Time dt, CommandQueue& Commands, SceneNode& target)
{
	Actionable* a = dynamic_cast<Actionable*>(&target);
	a->lock(mLock);
};

bool Lock::isFinnished() {
	return true;
};

void Lock::reset() {
}