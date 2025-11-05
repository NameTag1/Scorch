#pragma once

#include "Attack.h"
#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.hpp"

#include <SFML/Graphics.hpp>

class Slash : public Attack
{
public:
	Slash();
	Slash(int damage, unsigned int category, const TextureHolder& textures);

	virtual sf::FloatRect getBoundingRect() const;

	virtual Attack* clone() const;
	
	virtual sf::Vector2f getOffset();
	virtual void flip();

	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void updateCurrent(sf::Time dt, CommandQueue& Commands);

protected:
	Animation mAnimation;
};

