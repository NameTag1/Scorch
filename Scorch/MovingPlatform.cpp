#include "MovingPlatform.h"
#include "Utility.hpp"

MovingPlatform::MovingPlatform(TextureHolder& textureHolder, json data, sf::IntRect bounds)
	: mSprite(textureHolder.get(std::string(data["Texture"])), bounds)
	, Platform(data["Platform"])
	, mStartingPoint(data["StartingX"], data["StartingY"])
	, mEndPoint(data["EndX"], data["EndY"])
	, mSpeed(data["SpeedX"], data["SpeedY"])
	, mCushion(data["Cushion"])
	, mReturning(false)
	, mSpritePosition(0, 0)
	, mStartingPosition(getPosition())
	, mRunOnce(false)
{
};

void MovingPlatform::adust_for_platformer(Platformer& platformer) {
	if (!mReturning) {
		platformer.setPosition(platformer.getPosition().x + mSpeed.x, platformer.getPosition().y + mSpeed.y);
	}
	if (mReturning) {
		platformer.setPosition(platformer.getPosition().x - mSpeed.x, platformer.getPosition().y); //Y handled by gravity and platformer class
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
		mSpritePosition.x = adjustToNumber(mSpritePosition.x, mSpeed.x, float(mEndPoint.x));
		mSpritePosition.y = adjustToNumber(mSpritePosition.y, mSpeed.y, float(mEndPoint.y));
	} 
	else if (mReturning) {
		mSpritePosition.x = adjustToNumber(mSpritePosition.x, mSpeed.x, float(mStartingPoint.x));
		mSpritePosition.y = adjustToNumber(mSpritePosition.y, mSpeed.y, float(mStartingPoint.y));
	}

	setPosition(mStartingPosition+mSpritePosition);
};

void MovingPlatform::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(mSprite, states);
};