#include "NormalPlatform.h"


NormalPlatform::NormalPlatform(TextureHolder& textureHolder, json data)
: mSprite(textureHolder.get(std::string(data["Texture"])))
, Platform(data["Platform"])
{
}

NormalPlatform::NormalPlatform(TextureHolder& textureHolder, DataRetrivalType::Platforms type)
: mSprite(textureHolder.get(DATATABLE::platformData[type].texture))
, Platform(DATATABLE::platformData[type].friction, type)
{
};

NormalPlatform::NormalPlatform(TextureHolder& textureHolder, DataRetrivalType::Platforms type, sf::IntRect bounds)
: mSprite(textureHolder.get(DATATABLE::platformData[type].texture), bounds)
, Platform(DATATABLE::platformData[type].friction, type)
{
};

NormalPlatform::NormalPlatform(TextureHolder& textureHolder, NormalPlatformData data)
: mSprite(textureHolder.get(data.platform.texture), data.rect)
, Platform(data.platform.friction)
{
};

void NormalPlatform::setBounds(sf::IntRect newBounds) {
	mSprite.setTextureRect(newBounds);
}

sf::FloatRect NormalPlatform::getBoundingRect() const {
	return getWorldTransform().transformRect(mSprite.getGlobalBounds());
};

void NormalPlatform::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(mSprite, states);
};