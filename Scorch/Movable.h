#pragma once

#include "SceneNode.hpp"

class Movable : public SceneNode
{
public:
	explicit			Movable();
	void				setVelocity(sf::Vector2f velocity);
	void				setVelocity(float vx, float vy);
	void				accelerate(sf::Vector2f velocity);
	void				accelerate(float vx, float vy);
	sf::Vector2f		getVelocity() const;

	virtual std::vector<unsigned int> getCategory() const;

	void				destroy();
	virtual bool		isDestroyed() const;

	sf::Vector2i		lastKnownDirection();

protected:
	virtual void		updateCurrent(sf::Time dt, CommandQueue& commands);
	bool				mDestroyed;

private:
	sf::Vector2f		mVelocity;
	sf::Vector2i		mLastDirection;
};

