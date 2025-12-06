#include "AnimatedPlatform.h"


AnimatedPlatform::AnimatedPlatform(TextureHolder& textureHolder, json data)
: mAnimation(textureHolder, data["Animation"])
, Platform(data["Platform"])
{
}

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