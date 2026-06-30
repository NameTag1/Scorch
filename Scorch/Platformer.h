#ifndef Platformer_h
#define Platformer_h


#include<SFML/Graphics.hpp>

#include "Entity.hpp"
#include "Platform.h"

class Platformer : public Entity
{
public:
	enum platformState {
		grounded,
		drifting, //When applying acceleration one way, but moving the other bc of inertia
		running,
		walking,
		jumping,
		falling
	};

public:
	Platformer(int health);
	void adust_for_platform(Platform& p);

	virtual std::vector<unsigned int> getCategory() const;

	bool getOnPlatform();
	bool jump();
	void move(bool running, bool left);

	void setSpeed(float speed);

	platformState getPlatformState() const;

protected:
	virtual void updateCurrent(sf::Time dt, CommandQueue& Commands);

private:
	sf::FloatRect calculateOverlap(sf::FloatRect rect1, sf::FloatRect rect2);

private:
	bool onPlatform;
	float mRunSpeed;
	float mWalkFactor; //THIS IS A FACTOR OF RUN SPEED (e.g. 0.3)
	float mJumpPower;
	float maxMoveSpeed;
	platformState mPlatformState;

};
#endif

