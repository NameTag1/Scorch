
#include "Entity.hpp"

Entity::Entity(int hitpoints)
:	mMaxHitpoints(hitpoints)
,	mHitpoints(hitpoints)
{

}

//void Entity::setVelocity(sf::Vector2f velocity)
//{
//	mVelocity = velocity;
//}
//
//void Entity::setVelocity(float vx, float vy)
//{
//	mVelocity.x = vx;
//	mVelocity.y = vy;
//}
//
//sf::Vector2f Entity::getVelocity() const
//{
//	return mVelocity;
//}

std::vector<unsigned int> Entity::getCategory() const {
	std::vector<unsigned int> i = Movable::getCategory();
	i.push_back(Category::Entity);
	return i;
}

//void Entity::accelerate(sf::Vector2f velocity)
//{
//	mVelocity += velocity;
//}
//
//void Entity::accelerate(float vx, float vy)
//{
//	mVelocity.x += vx;
//	mVelocity.y += vy;
//}

void Entity::updateCurrent(sf::Time dt, CommandQueue& commands)
{	
	Movable::updateCurrent(dt, commands);
	/*move(mVelocity * dt.asSeconds());
	if (mVelocity.x != 0) {
		mLastDirection.x = mVelocity.x;
	}
	if (mVelocity.y != 0) {
		mLastDirection.y = mVelocity.y;
	}*/
}

int Entity::getHitpoints() {
	return mHitpoints;
}

void Entity::heal(int heal) {
	assert(heal > 0);
	mHitpoints += heal;
	if (mHitpoints > mMaxHitpoints) {
		mHitpoints = mMaxHitpoints;
	}
}

void Entity::damage(int damage) {
	assert(damage > 0);
	mHitpoints -= damage;
	if (mHitpoints < 0) {
		mHitpoints = 0;
	}
}

bool Entity::isDestroyed() const {
	return mHitpoints <= 0;
}

//sf::Vector2i Entity::lastKnownDirection()
//{
//	return mLastDirection;
//}


