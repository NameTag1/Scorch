#include "FleePlayer.h"

#include "Player_Entity.h"

FleePlayer::FleePlayer(int distance)
: distance(distance)
, Action(Action::Persistent)
{
}

void FleePlayer::update(sf::Time dt, CommandQueue& Commands, SceneNode& target)
{
	Platformer* platformer = dynamic_cast<Platformer*>(&target);
	sf::Vector2f playerPos = Player_Entity::getInstance()->getWorldPosition();

	bool left = false;
	if (playerPos.x > platformer->getWorldPosition().x) {
		left = true;
	}

	if (!isFinnished()) {
		platformer->move(left);
	}
	mLastPos = platformer->getWorldPosition();
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