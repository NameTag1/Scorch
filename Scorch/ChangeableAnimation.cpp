#include "ChangeableAnimation.h"

ChangeableAnimation::ChangeableAnimation()
: mCurrentAnimation()
, mDefaultAnimation()
{
}

void ChangeableAnimation::update(sf::Time dt)
{
	// Nothing to do if we have no animations
	if (mAnimations.empty())
		return;

	// Find current animation; fall back to default if needed
	auto it = mAnimations.find(mCurrentAnimation);
	if (it == mAnimations.end())
		it = mAnimations.find(mDefaultAnimation);

	// If still not found, nothing to update
	if (it == mAnimations.end())
		return;

	// If finished, switch to default (if available)
	if (it->second.isFinished()) {
		if (!mDefaultAnimation.empty()) {
			mCurrentAnimation = mDefaultAnimation;
			it = mAnimations.find(mCurrentAnimation);
		}
		// if default not found, keep using `it` (which may be finished) — safe guard below will handle update
	}

	// Re-check iterator validity (default might not exist)
	if (it != mAnimations.end())
		it->second.update(dt);
}

void ChangeableAnimation::changeAnimation(std::string Animation, sf::Time mResetDuration)
{
	// Ensure an entry exists (operator[] will default-construct if missing),
	// then configure and set current.
	auto &anim = mAnimations[Animation];
	anim.setDuration(mResetDuration);
	anim.restart();
	mCurrentAnimation = std::move(Animation);
}

void ChangeableAnimation::pushAnimation(std::string animation, TextureHolder& textureHolder, json animationData)
{
	Animation anim(textureHolder, animationData);
	mAnimations.emplace(std::move(animation), std::move(anim));
	// If this is the first animation added, set as default
	if (mAnimations.size() == 1) {
		mDefaultAnimation = mAnimations.begin()->first;
		mCurrentAnimation = mDefaultAnimation;
	}
}

void ChangeableAnimation::setToDefault()
{
	if (mDefaultAnimation.empty())
		return;

	auto it = mAnimations.find(mDefaultAnimation);
	if (it != mAnimations.end()) {
		mCurrentAnimation = mDefaultAnimation;
		it->second.restart();
	}
}

sf::FloatRect ChangeableAnimation::getLocalBounds() const
{
	if (mAnimations.empty())
		return sf::FloatRect();

	auto it = mAnimations.find(mCurrentAnimation);
	if (it == mAnimations.end())
		it = mAnimations.find(mDefaultAnimation);

	if (it == mAnimations.end())
		return sf::FloatRect();

	return it->second.getLocalBounds();
}

sf::FloatRect ChangeableAnimation::getGlobalBounds() const
{
	if (mAnimations.empty())
		return sf::FloatRect();

	auto it = mAnimations.find(mCurrentAnimation);
	if (it == mAnimations.end())
		it = mAnimations.find(mDefaultAnimation);

	if (it == mAnimations.end())
		return sf::FloatRect();

	return it->second.getGlobalBounds();
}

void ChangeableAnimation::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (mAnimations.empty())
		return;

	auto it = mAnimations.find(mCurrentAnimation);
	if (it == mAnimations.end())
		it = mAnimations.find(mDefaultAnimation);

	if (it == mAnimations.end())
		return;

	target.draw(it->second, states);
}
