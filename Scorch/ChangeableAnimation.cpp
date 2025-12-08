#include "ChangeableAnimation.h"
#include "Logger.h"

ChangeableAnimation::ChangeableAnimation()
: mCurrentAnimation("")
, mDefaultAnimation("")
{
}

ChangeableAnimation::ChangeableAnimation(const TextureHolder& textures, json data)
: mCurrentAnimation("")
, mDefaultAnimation("")
{
	// Expecting either:
	// - data["Animations"] is an object { "Idle": { ... }, "Run": { ... } }
	// - OR data["Animations"] is an array [ { "Name":"Idle", ... }, { "Name":"Run", ... } ]
	if (!data.contains("Animations"))
		return;

	const json& animations = data["Animations"];

	if (animations.is_object())
	{
		// Keys are animation names
		for (auto it = animations.begin(); it != animations.end(); ++it)
		{
			std::string name = it.key();
			const json& animJson = it.value();
			Animation anim(textures, animJson);
			Logger::Instance->LogData(Logger::Action, "Creating ChangeableAnimation \"" + name + "\" from JSON");
			addAnimation(name, std::move(anim));
		}
	}

	// default animation name (optional)
	if (data.contains("Default"))
		mDefaultAnimation = data["Default"];
}

void ChangeableAnimation::setAnimation(std::string Animation)
{
	auto it = mAnimations.find(Animation);
	if (it != mAnimations.end()) {
		mCurrentAnimation = Animation;
		it->second.restart();
	}
}

void ChangeableAnimation::setAnimation(std::string Animation, sf::Time mResetDuration)
{
	auto it = mAnimations.find(Animation);
	if (it != mAnimations.end()) {
		mCurrentAnimation = Animation;
		it->second.setDuration(mResetDuration);
		it->second.restart();
	}
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

void ChangeableAnimation::addAnimation(const std::string& name, Animation animation)
{
	// store (move) animation into map
	mAnimations[name] = std::move(animation);

	// if no default/current set, use first added
	if (mDefaultAnimation.empty())
		mDefaultAnimation = name;
	if (mCurrentAnimation.empty())
		mCurrentAnimation = name;
}

void ChangeableAnimation::setDefaultAnimation(const std::string& name)
{
	if (mAnimations.find(name) != mAnimations.end())
		mDefaultAnimation = name;
}
