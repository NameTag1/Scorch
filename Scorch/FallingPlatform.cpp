#include "FallingPlatform.h"
#include <iostream>


FallingPlatform::FallingPlatform(TextureHolder& textureHolder, DataRetrivalType::Platforms type)
: mAnimation(textureHolder.get(DATATABLE::fallingPlatformData[type].platform.texture))
, Platform(DATATABLE::fallingPlatformData[type].platform.friction, type)
, mActivated(false)
, mReset(DATATABLE::fallingPlatformData[type].resetTime)
{
	mAnimation.setFrameSize(DATATABLE::fallingPlatformData[type].animation.mFrameSize);
	mAnimation.setNumFrames(DATATABLE::fallingPlatformData[type].animation.mNumFrames);
	mAnimation.setDuration(DATATABLE::fallingPlatformData[type].animation.mDuration);
	mAnimation.setRepeating(DATATABLE::fallingPlatformData[type].animation.mRepeat);
	mAnimation.update(sf::seconds(0));
};


void FallingPlatform::adust_for_platformer(Platformer& platformer) {
	mActivated = true;
}

void FallingPlatform::updateCurrent(sf::Time dt, CommandQueue& Commands) {
	if (mActivated) {
		mReset -= dt;
		if (!mAnimation.isFinished()) {
			mAnimation.update(dt);
		}
		if (mReset <= sf::seconds(0)) {
			mReset = DATATABLE::fallingPlatformData[Platform::getPlatformType()].resetTime;
			mAnimation.restart();
			mAnimation.update(sf::seconds(0));
			mActivated = false;
		}
	}
};


std::vector<unsigned int> FallingPlatform::getCategory() const {
	std::vector<unsigned int> i;
	if (!mAnimation.isFinished()) {
		i.push_back(Category::Platform);
	}
	return i;
}

sf::FloatRect FallingPlatform::getBoundingRect() const {
	return getWorldTransform().transformRect(mAnimation.getGlobalBounds());
};

void FallingPlatform::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
	if (!mAnimation.isFinished()) {
		target.draw(mAnimation, states);
	}
};
