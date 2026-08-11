#pragma once

#include "SceneNode.hpp"

class Movable : public SceneNode
{
public:
	explicit			Movable();
	explicit			Movable(float weight);
	void				setVelocity(sf::Vector2f velocity);
	void				setVelocity(float vx, float vy);

	void				changeVelocity(sf::Vector2f velocity);
	void				changeVelocity(float vx, float vy);

	//THIS IS AFFECTED BY TIME
	void				accelerate(sf::Vector2f velocity);
	void				accelerate(float ax, float ay);

	void				applyForce(sf::Vector2f force); //In Newtons, F=m*a
	void				applyForce(float fx, float fy);

	void				applyInstantaneousForce(sf::Vector2f force); //In Newtons, F=m*a
	void				applyInstantaneousForce(float fx, float fy);

	sf::Vector2f		getVelocity() const;

	void				setWeight(float newWeight);
	void				changeWeight(float modification);
	float				getWeight() const;

	virtual std::vector<unsigned int> getCategory() const;

	void				destroy();
	virtual bool		isDestroyed() const;

	sf::Vector2i		lastKnownDirection();
	sf::Vector2i		lastKnownAcceleration();

protected:
	virtual void		updateCurrent(sf::Time dt, CommandQueue& commands);
	bool				mDestroyed;

private:
	float				mMass; //In kg
	sf::Vector2f		mForceAccumulator;
	sf::Vector2f		mForceInstantaneousAccumulator; //Like a force, but only applied for one frame (e.g. knockback, jump)
	sf::Vector2f		mVelocity; //In m/s
	sf::Vector2i		mLastDirection; //Last direction entity moved
	sf::Vector2i		mLastAcceleration; //Last direction entity attempted (accelerated) to move
};

