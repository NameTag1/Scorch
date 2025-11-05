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
	bool jump();
	void move(bool left);

	void setSpeed(double speed);

protected:
	virtual void updateCurrent(sf::Time dt, CommandQueue& Commands);

private:
	sf::FloatRect calculateOverlap(sf::FloatRect rect1, sf::FloatRect rect2);

private:
	bool onPlatform;
	double mSpeed;
	double mJumpPower;
	double maxMoveSpeed;

};
#endif

