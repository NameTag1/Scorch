#include "MoveDis.h"
#include <iostream>

MoveDis::MoveDis(int distance)
: mLeft((distance < 0)? true : false)
, mStart()
, mDistance(distance)
, mDistanceTraveled(0)
, Action(Persistent)
{
}

void MoveDis::update(sf::Time dt, CommandQueue& Commands, SceneNode& target) 
{
	Platformer* platformer = dynamic_cast<Platformer*>(&target);
	if (mStart == sf::Vector2f()) {
		mStart = platformer->getWorldPosition();
	}
	platformer->move(mLeft);
	mDistanceTraveled += (platformer->getWorldPosition() - mStart).x;
};

bool MoveDis::isFinnished() {
	if (mDistance < 0) {
		return mDistance >= mDistanceTraveled;
	}
	else {
		return mDistance <= mDistanceTraveled;
	}
};

void MoveDis::reset() {
	mStart = sf::Vector2f();
	mDistanceTraveled = 0;
}