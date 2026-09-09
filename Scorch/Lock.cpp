#include "Lock.h"

Lock::Lock(bool mLocked)
: mLock(mLocked)
, Action(Action::RunOnce)
, mTarget(nullptr)
{
}

void Lock::update(sf::Time dt, CommandQueue& Commands, SceneNode& target)
{
	if (mTarget == nullptr) {
		if (Player_Entity* castedPtr = dynamic_cast<Player_Entity*>(&target)) {
			mTarget = castedPtr;
		}
		//mTarget = safeCast<Player_Entity*, SceneNode*>(&target);
	}
	mTarget->lock(mLock);
};

bool Lock::isFinnished() {
	return true;
};

void Lock::reset() {
}