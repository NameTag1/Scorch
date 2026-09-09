#pragma once

#include <vector>

#include "Platformer.h"

class PlatformerMovementSuite : public Platformer
{
public:
	enum PlatformerState {
		Static,
		Sliding,
		Braking, //Accelerating oposite of velocity
		Running,
		Walking,
	};

public:
	PlatformerMovementSuite();

	virtual void updateCurrent(sf::Time dt, CommandQueue& Commands);

	virtual bool jump();
	virtual bool dash(bool left);
	virtual void move(bool running, bool left);

	virtual std::vector<unsigned int> getCategory() const;

	void setSpeed(float speed);
	void braking(bool isBraking);

private:
	PlatformerState mPlatformState;

	bool brakingEnabled; //This is what enables braking when no input is given, handled in ADUST_FOR_PLATFORM and MOVE

	// Last intended horizontal force applied by player this frame (in Newtons). Set by move().
	float mIntendedForceX;

	float mAcceleration;
	float mMaxSpeed;

	float mDashPower;

	float mWalkFactor; //THIS IS A FACTOR OF RUN FORCE (e.g. 0.3)
	float mJumpPower;
	float mFallControl; //Factor of how much player can move while falling

};

