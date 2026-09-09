#include "PlatformerMovementSuite.h"

#include "Logger.h"

PlatformerMovementSuite::PlatformerMovementSuite()
: Platformer()
, brakingEnabled(true)
, mAcceleration(30.f) //meters per second^2
, mMaxSpeed(6.5f) //meters per second
, mWalkFactor(0.3f)
, mDashPower(1000.f) //In N
, mJumpPower(500.f) //In N
, mIntendedForceX(0.f)
, mFallControl(0.1f)
, mPlatformState(PlatformerState::Static)
{

}

bool PlatformerMovementSuite::jump() {
	if (getOnPlatform() && Movable::getVelocity().y >= 0) {
		Movable::setVelocity(Movable::getVelocity().x, 0);
		Movable::applyInstantaneousForce(0, -mJumpPower);
		return true;
	}
	else {
		return false;
	}
}

bool PlatformerMovementSuite::dash(bool left) {
	if (Movable::lastKnownAcceleration().x > 0) {
		Movable::applyInstantaneousForce(mDashPower, 0);
		Logger::Instance->LogData(Logger::Action, "Dashed");
	}
	else if (Movable::lastKnownAcceleration().x < 0) {
		Movable::applyInstantaneousForce(-mDashPower, 0);
		Logger::Instance->LogData(Logger::Action, "Dashed");
	}
	else {
		Logger::Instance->LogData(Logger::Action, "FAIL");
		return false;
	}
	return true;
};

void PlatformerMovementSuite::move(bool running, bool left) {
	float appliedForce = (running) ? mAcceleration * getWeight() : mAcceleration * mWalkFactor * getWeight();

	if (!getOnPlatform()/* && mPlatformState != falling*/) {
		appliedForce *= mFallControl; // Reduce horizontal control while falling
	}

	float vx = Movable::getVelocity().x;
	// Determine intended horizontal direction: -1 for left, +1 for right
	int intendedDir = (left) ? -1 : 1;

	// Record intended force for friction/static friction checks
	mIntendedForceX = (left ? -appliedForce : appliedForce);

	// Only apply force if we haven't reached the signed max speed in the intended direction.
	if (left && Movable::getVelocity().x > -mMaxSpeed) {
		Movable::applyForce(mIntendedForceX, 0);
	}
	else if (!left && Movable::getVelocity().x < mMaxSpeed) {
		Movable::applyForce(mIntendedForceX, 0);
	}
}

std::vector<unsigned int> PlatformerMovementSuite::getCategory() const
{
	std::vector<unsigned int> i(Platformer::getCategory());
	i.push_back(Category::PlatformerMover);
	return i;
}

void PlatformerMovementSuite::setSpeed(float speed)
{
	mMaxSpeed = speed;
}

void PlatformerMovementSuite::braking(bool isBraking)
{
	brakingEnabled = isBraking;
}

void PlatformerMovementSuite::updateCurrent(sf::Time dt, CommandQueue& Commands) {
	// Braking Stuff
	if (mIntendedForceX != 0.f && brakingEnabled) {
		float vx = getVelocity().x;

		// moving: apply kinetic friction opposing motion
		if (vx > 0) {
			if (brakingEnabled && mIntendedForceX < 0) {
				Movable::applyForce(-mAcceleration * getWeight(), 0);
			}
		}
		else if (vx < 0) {
			if (brakingEnabled && mIntendedForceX > 0) {
				Movable::applyForce(mAcceleration * getWeight(), 0);
			}
		}
	}

	// Reset intended input force; move() will set this if input is present this frame
	mIntendedForceX = 0.f;
	Platformer::updateCurrent(dt, Commands);
};