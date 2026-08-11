#include "Movable.h"
#include "Utility.hpp"

Movable::Movable()
: mDestroyed(false)
, mVelocity()
, mForceAccumulator()
, mMass(50)
{

}

Movable::Movable(float weight)
: mDestroyed(false)
, mVelocity()
, mMass(weight)
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

void Movable::changeVelocity(sf::Vector2f velocity)
{
	mVelocity += velocity;
}

void Movable::changeVelocity(float vx, float vy)
{
	mVelocity.x += vx;
	mVelocity.y += vy;
}

sf::Vector2f Movable::getVelocity() const
{
	return mVelocity;
}

void Movable::setWeight(float newWeight)
{
	mMass = newWeight;
}

void Movable::changeWeight(float modification)
{
	mMass += modification;
}

float Movable::getWeight() const
{
	return mMass;
}

void Movable::accelerate(sf::Vector2f velocity)
{
	mForceAccumulator += (velocity * mMass); //Everything handled in Force Buffer, accel like gravity is multiplied by weight to get force
}

void Movable::accelerate(float vx, float vy)
{
	//Everything handled in Force Buffer, accel like gravity is multiplied by weight to get force
	mForceAccumulator.x += vx * mMass;
	mForceAccumulator.y += vy * mMass;
}

void Movable::applyForce(sf::Vector2f force)
{
	mForceAccumulator += force;
}

void Movable::applyForce(float fx, float fy)
{
	mForceAccumulator.x += fx;
	mForceAccumulator.y += fy;
}

void Movable::applyInstantaneousForce(sf::Vector2f force)
{
	mForceInstantaneousAccumulator += force;
}

void Movable::applyInstantaneousForce(float fx, float fy)
{
	mForceInstantaneousAccumulator.x += fx;
	mForceInstantaneousAccumulator.y += fy;
}

std::vector<unsigned int> Movable::getCategory() const {
	std::vector<unsigned int> i;
	i.push_back(Category::Movable);
	return i;
}

void Movable::updateCurrent(sf::Time dt, CommandQueue& commands)
{
	//dt multiplied to force to get acceleration, then divided by mass to get velocity change. 
	//Instantaneous forces are applied without dt, as they are meant to be applied for one frame only.
	changeVelocity(mForceAccumulator.x / mMass * dt.asSeconds(), mForceAccumulator.y / mMass * dt.asSeconds());
	changeVelocity(mForceInstantaneousAccumulator.x / mMass, mForceInstantaneousAccumulator.y / mMass);
	mForceAccumulator = sf::Vector2f(0, 0);
	mForceInstantaneousAccumulator = sf::Vector2f(0, 0);

	//dt multiplied to velocity to get distance, then converted to pixels and moved.
	move(meterToPixel(mVelocity * dt.asSeconds()));
	if (mVelocity.x != 0) {
		mLastDirection.x = int(mVelocity.x);
	}
	if (mVelocity.y != 0) {
		mLastDirection.y = int(mVelocity.y);
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

sf::Vector2i Movable::lastKnownAcceleration()
{
	return mLastAcceleration;
}


