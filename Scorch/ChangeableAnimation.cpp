#include "ChangeableAnimation.h"

ChangeableAnimation::ChangeableAnimation()
: mCurrentAnimation(0)
, mDefaultAnimation(0)
{
}

void ChangeableAnimation::update(sf::Time dt)
{
	if (mAnimations[mCurrentAnimation].isFinished()) {
		mCurrentAnimation = mDefaultAnimation;
	}
	mAnimations[mCurrentAnimation].update(dt);
}

void ChangeableAnimation::setAnimation(unsigned int Animation, sf::Time Duration)
{
	mCurrentAnimation = Animation;
	mAnimations[mCurrentAnimation].setDuration(Duration);
	mAnimations[mCurrentAnimation].restart();
}

void ChangeableAnimation::setToDefault()
{
	mCurrentAnimation = mDefaultAnimation;
	mAnimations[mCurrentAnimation].restart();
}

sf::FloatRect ChangeableAnimation::getLocalBounds() const
{
	return mAnimations[mCurrentAnimation].getLocalBounds();
}

sf::FloatRect ChangeableAnimation::getGlobalBounds() const
{
	return mAnimations[mCurrentAnimation].getGlobalBounds();
}

void ChangeableAnimation::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mAnimations[mCurrentAnimation], states);
}
