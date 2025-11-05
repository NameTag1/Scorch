#pragma once

#include "Platform.h"
#include "DataTable.h"
#include "ResourceHolder.hpp"
#include <SFML/Graphics.hpp>

class Platformer;

class MovingPlatform : public Platform
{
public:
	MovingPlatform(TextureHolder& textureHolder, DataRetrivalType::Platforms type);
	MovingPlatform(TextureHolder& textureHolder, DataRetrivalType::Platforms type, sf::IntRect bounds);
	virtual void adust_for_platformer(Platformer& platformer);
	void setBounds(sf::IntRect newBounds);
	virtual sf::FloatRect getBoundingRect() const;

private:
	virtual void updateCurrent(sf::Time dt, CommandQueue& commands);
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	sf::Sprite mSprite;
	sf::Vector2i mStartingPoint;
	sf::Vector2i mEndPoint;
	sf::Vector2f mSpeed;
	float mCushion;
	bool mReturning;
	sf::Vector2f mStartingPosition;
	sf::Vector2f mSpritePosition;

	bool mRunOnce;
};
