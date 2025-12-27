#pragma once

#include "SceneNode.hpp"
#include "ResourceIdentifiers.hpp"
#include <SFML/Graphics/RectangleShape.hpp>

class SkyBackground : public SceneNode
{
public:
	SkyBackground(TextureHolder& textures);

private:
	sf::RectangleShape mBackground;

	virtual void			updateCurrent(sf::Time dt, CommandQueue& commands);
	virtual void			draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

