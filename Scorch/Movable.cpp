#include "Movable.h"

Movable::Movable()
: mDestroyed(false)
, mVelocity()
{

}

void Movable::setVelocity(sf::Vector2f velocity)
{
	mVelocity = velocity;
}

void Movable::setVelocity(float vx, float vy)
{
	mVelocity.x = vx;
	mVelocity.y = vy;
}

sf::Vector2f Movable::getVelocity() const
{
	return mVelocity;
}

std::vector<unsigned int> Movable::getCategory() const {
	std::vector<unsigned int> i;
	i.push_back(Category::Movable);
	return i;
}

void Movable::accelerate(sf::Vector2f velocity)
{
	mVelocity += velocity;
}

void Movable::accelerate(float vx, float vy)
{
	mVelocity.x += vx;
	mVelocity.y += vy;
}

void Movable::updateCurrent(sf::Time dt, CommandQueue& commands)
{
	move(mVelocity * dt.asSeconds());
	if (mVelocity.x != 0) {
		mLastDirection.x = mVelocity.x;
	}
	if (mVelocity.y != 0) {
		mLastDirection.y = mVelocity.y;
	}
}

void Movable::destroy() {
	mDestroyed = true;
}

bool Movable::isDestroyed() const {
	return mDestroyed;
}

sf::Vector2i Movable::lastKnownDirection()
{
	return mLastDirection;
}


