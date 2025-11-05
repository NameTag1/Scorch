#include "ChasePlayer.h"
#include "Player_Entity.h"

ChasePlayer::ChasePlayer(int distance)
: distance(distance)
, Action(Action::Persistent)
{
}

void ChasePlayer::update(sf::Time dt, CommandQueue& Commands, SceneNode& target)
{
	Platformer* platformer = dynamic_cast<Platformer*>(&target);
	sf::Vector2f playerPos = Player_Entity::getInstance()->getWorldPosition();

	bool left = false;
	if (playerPos.x < platformer->getWorldPosition().x) {
		left = true;
	}

	if (!isFinnished()) {
		platformer->move(left);
	}
	mLastPos = platformer->getWorldPosition();
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