
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
	std::vector<unsigned int> i;
	i.push_back(Category::Entity);
	return i;
}

int Entity::getHitpoints() {
	return mHitpoints;
}

int Entity::getMaxHitpoints()
{
	return mMaxHitpoints;
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


