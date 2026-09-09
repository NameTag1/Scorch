#include "FleePlayer.h"

#include "Player_Entity.h"

FleePlayer::FleePlayer(int distance)
: distance(distance)
, Action(Action::Persistent)
{
}

void FleePlayer::update(sf::Time dt, CommandQueue& Commands, SceneNode& target)
{
	if (mTarget == nullptr) {
		if (Platformer* castedPtr = dynamic_cast<Platformer*>(&target)) {
			mTarget = castedPtr;
		}
		//mTarget = safeCast<Platformer*, SceneNode*>(&target);
	}
	sf::Vector2f playerPos = Player_Entity::getInstance()->getWorldPosition();

	bool left = false;
	if (playerPos.x > mTarget->getWorldPosition().x) {
		left = true;
	}

	if (!isFinnished()) {
		mTarget->move(true, left);
	}
	mLastPos = mTarget->getWorldPosition();
};

bool FleePlayer::isFinnished() {
	sf::Vector2f playerPos = Player_Entity::getInstance()->getWorldPosition();
	if (playerPos.x <= -distance + mLastPos.x || playerPos.x >= distance + mLastPos.x) {
		return true;
	}
	else {
		return false;
	}
};

void FleePlayer::reset() {
}