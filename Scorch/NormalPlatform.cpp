#include "NormalPlatform.h"


NormalPlatform::NormalPlatform(TextureHolder& textureHolder, json data, sf::IntRect bounds)
: mSprite(textureHolder.get(std::string(data["Texture"])), bounds)
, Platform(data["Platform"])
{
}

void NormalPlatform::setBounds(sf::IntRect newBounds) {
	mSprite.setTextureRect(newBounds);
}

sf::FloatRect NormalPlatform::getBoundingRect() const {
	return getWorldTransform().transformRect(mSprite.getGlobalBounds());
};

void NormalPlatform::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(mSprite, states);
};