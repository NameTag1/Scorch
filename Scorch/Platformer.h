#ifndef Platformer_h
#define Platformer_h


#include<SFML/Graphics.hpp>

#include "Entity.hpp"
#include "Platform.h"

class Platformer : public Entity
{
public:
	Platformer(int health);
	void adust_for_platform(Platform& p);

	virtual std::vector<unsigned int> getCategory() const;

	bool getOnPlatform();
	virtual bool jump();
	virtual bool dash(bool left);
	virtual void move(bool running, bool left);

	void setSpeed(float speed);
	void braking(bool isBraking);

protected:
	virtual void updateCurrent(sf::Time dt, CommandQueue& Commands);

private:
	sf::FloatRect calculateOverlap(sf::FloatRect rect1, sf::FloatRect rect2);

private:
	bool onPlatform;
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
#endif

