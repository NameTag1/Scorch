#include "Slash.h"
#include <iostream>

Slash::Slash()
: Attack()
{

}

Slash::Slash(int damage, unsigned int category, const TextureHolder& textures)
: Attack(damage, category)
, mAnimation(textures.get(Textures::Slash))
{
	mAnimation.setDuration(sf::seconds(0.1));
	mAnimation.setFrameSize(sf::Vector2i(50, 120));
	mAnimation.setNumFrames(4);
	mCooldown = sf::seconds(0.1);
	mDuration = sf::seconds(0.1);
	mOffset = sf::Vector2f(30, -mAnimation.getFrameSize().y/2);
};

sf::FloatRect Slash::getBoundingRect() const {
	return getWorldTransform().transformRect(mAnimation.getGlobalBounds());
}

Attack* Slash::clone() const
{
	Slash* s = new Slash();
	s->mDamage = mDamage;
	s->mTarget = mTarget;
	s->mCooldown = mCooldown;
	s->mOffset = mOffset;
	s->mDuration = mDuration;
	s->mLifetime = mLifetime;
	s->mAnimation = mAnimation;
	s->mLifetime = mLifetime;
	return s;
}

sf::Vector2f Slash::getOffset()
{
	if (left) {
		mOffset.x = -mOffset.x;
	}
	return mOffset;
}

void Slash::flip()
{
	mAnimation.flip(left, false);
}

void Slash::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(mAnimation, states);
};

void Slash::updateCurrent(sf::Time dt, CommandQueue& Commands) {
	Attack::updateCurrent(dt, Commands);
	mAnimation.update(dt);
};