#include "ChasePlayer.h"
#include "Player_Entity.h"

ChasePlayer::ChasePlayer(int distance)
: distance(distance)
, Action(Action::Persistent)
{
}

void ChasePlayer::update(sf::Time dt, CommandQueue& Commands, SceneNode& target)
{
	if (mTarget == nullptr) {
		if (Platformer* castedPtr = dynamic_cast<Platformer*>(&target)) {
			mTarget = castedPtr;
		}
	}
	sf::Vector2f playerPos = Player_Entity::getInstance()->getWorldPosition();

	bool left = false;
	if (playerPos.x < mTarget->getWorldPosition().x) {
		left = true;
	}

	if (!isFinnished()) {
		mTarget->move(true, left);
	}
	mLastPos = mTarget->getWorldPosition();
};

bool ChasePlayer::isFinnished() {
	sf::Vector2f playerPos = Player_Entity::getInstance()->getWorldPosition();
	if (playerPos.x-mLastPos.x >= -distance && playerPos.x-mLastPos.x <= distance) {
		return true;
	}
	else {
		return false;
	}
};

void ChasePlayer::reset() {
}