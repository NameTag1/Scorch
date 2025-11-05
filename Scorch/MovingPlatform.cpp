#include "MovingPlatform.h"
#include "Utility.hpp"
#include <iostream>


MovingPlatform::MovingPlatform(TextureHolder& textureHolder, DataRetrivalType::Platforms type)
: mSprite(textureHolder.get(DATATABLE::movingPlatformData[type].platform.texture))
, Platform(DATATABLE::movingPlatformData[type].platform.friction, type)
, mStartingPoint(DATATABLE::movingPlatformData[type].startingPoint)
, mEndPoint(DATATABLE::movingPlatformData[type].endPoint)
, mSpeed(DATATABLE::movingPlatformData[type].speed)
, mCushion(DATATABLE::movingPlatformData[type].cushion)
, mReturning(false)
, mSpritePosition(0,0)
, mStartingPosition(getPosition())
, mRunOnce(false)
{
};

MovingPlatform::MovingPlatform(TextureHolder& textureHolder, DataRetrivalType::Platforms type, sf::IntRect bounds)
: mSprite(textureHolder.get(DATATABLE::platformData[type].texture), bounds)
, Platform(DATATABLE::platformData[type].friction, type)
, mStartingPoint(DATATABLE::movingPlatformData[type].startingPoint)
, mEndPoint(DATATABLE::movingPlatformData[type].endPoint)
, mSpeed(DATATABLE::movingPlatformData[type].speed)
, mCushion(DATATABLE::movingPlatformData[type].cushion)
, mReturning(false)
, mSpritePosition(0, 0)
, mStartingPosition(getPosition())
, mRunOnce(false)
{
};

void MovingPlatform::adust_for_platformer(Platformer& platformer) {
	if (!mReturning) {
		platformer.setPosition({ platformer.getPosition().x + mSpeed.x, platformer.getPosition().y + mSpeed.y });
	}
	if (mReturning) {
		platformer.setPosition({ platformer.getPosition().x - mSpeed.x, platformer.getPosition().y }); //Y handled by gravity and platformer class
	}
};

void MovingPlatform::setBounds(sf::IntRect newBounds) {
	mSprite.setTextureRect(newBounds);
}

sf::FloatRect MovingPlatform::getBoundingRect() const {
	return getWorldTransform().transformRect(mSprite.getGlobalBounds());
};

void MovingPlatform::updateCurrent(sf::Time dt, CommandQueue& commands) {

	if (!mRunOnce) {
		mStartingPosition = getPosition(); //Position setting happens after platform created (constructor)
		mRunOnce = true;
	}

	if (mSpritePosition.x == mStartingPoint.x && mSpritePosition.y == mStartingPoint.y) {
		mReturning = false;
	}
	else if (mSpritePosition.x == mEndPoint.x && mSpritePosition.y == mEndPoint.y) {
		mReturning = true;
	};

	if (!mReturning) {
		mSpritePosition.x = adjustToNumber(mSpritePosition.x, mSpeed.x, mEndPoint.x);
		mSpritePosition.y = adjustToNumber(mSpritePosition.y, mSpeed.y, mEndPoint.y);
	} 
	else if (mReturning) {
		mSpritePosition.x = adjustToNumber(mSpritePosition.x, mSpeed.x, mStartingPoint.x);
		mSpritePosition.y = adjustToNumber(mSpritePosition.y, mSpeed.y, mStartingPoint.y);
	}

	setPosition(mStartingPosition+mSpritePosition);
};

void MovingPlatform::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(mSprite, states);
};