#include "Image.h"

#include <SFML/Graphics.hpp>


namespace GUI
{

	Image::Image(const TextureHolder& textures, Textures::ID id)
	{
		mSprite.setTexture(textures.get(id));
	}

	void Image::updateImage(const TextureHolder& textures, Textures::ID id)
	{
		mSprite.setTexture(textures.get(id));
	}

	bool Image::isSelectable() const
	{
		return false;
	}

	void Image::handleEvent(const sf::Event&)
	{
	}

	void Image::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		target.draw(mSprite, states);
	}


	void Image::updateRect(sf::FloatRect parrentRect)
	{
		Component::updateRect(parrentRect);

		mRect.scaleSprite(mSprite, true);
	}

}