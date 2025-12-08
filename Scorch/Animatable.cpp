#include "Animatable.h"

Animatable::Animatable()
	: mAnimations()
{
}

Animatable::Animatable(const TextureHolder& textures, json data)
	: mAnimations(textures, data)
{
}

void Animatable::setAnimation(std::string Animation)
{
	mAnimations.setAnimation(Animation);
}

void Animatable::setAnimation(std::string Animation, sf::Time mResetDuration)
{
	mAnimations.setAnimation(Animation, mResetDuration);
}

void Animatable::update(sf::Time dt)
{
	mAnimations.update(dt);
}

void Animatable::setToDefault()
{
	mAnimations.setToDefault();
}

sf::FloatRect Animatable::getLocalBounds() const
{
	return mAnimations.getLocalBounds();
}

sf::FloatRect Animatable::getGlobalBounds() const
{
	return mAnimations.getGlobalBounds();
}

void Animatable::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mAnimations, states);
}

void Animatable::addAnimation(const std::string& name, Animation animation)
{
	mAnimations.addAnimation(name, animation);
}

void Animatable::setDefaultAnimation(const std::string& name)
{
	mAnimations.setDefaultAnimation(name);
}