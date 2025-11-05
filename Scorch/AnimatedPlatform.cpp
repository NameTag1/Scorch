#include "AnimatedPlatform.h"
#include <iostream>


AnimatedPlatform::AnimatedPlatform(TextureHolder& textureHolder, DataRetrivalType::Platforms type)
: mAnimation(textureHolder.get(DATATABLE::animatedPlatformData[type].platform.texture))
, Platform(DATATABLE::animatedPlatformData[type].platform.friction, type)
{
	mAnimation.setFrameSize(DATATABLE::animatedPlatformData[type].animation.mFrameSize);
	mAnimation.setNumFrames(DATATABLE::animatedPlatformData[type].animation.mNumFrames);
	mAnimation.setDuration(DATATABLE::animatedPlatformData[type].animation.mDuration);
	mAnimation.setRepeating(DATATABLE::animatedPlatformData[type].animation.mRepeat);
};

void AnimatedPlatform::adust_for_platformer(Platformer& platformer) {

};

void AnimatedPlatform::updateCurrent(sf::Time dt, CommandQueue& Commands) {
	mAnimation.update(dt);
};

sf::FloatRect AnimatedPlatform::getBoundingRect() const {
	return getWorldTransform().transformRect(mAnimation.getGlobalBounds());
};

void AnimatedPlatform::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(mAnimation, states);
};