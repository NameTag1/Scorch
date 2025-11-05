#pragma once

#include "Weapon.h"
#include "ResourceIdentifiers.hpp"

class Greatsword : public Weapon
{
public:
	Greatsword(const TextureHolder& textures, Category::Type type);
	virtual void flip();
	virtual void updateCurrent(sf::Time dt, CommandQueue& commands);
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	sf::Sprite mSprite;
	bool flipped;
};

