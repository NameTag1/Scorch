#pragma once

#include "Weapon.h"
#include "ResourceIdentifiers.hpp"

class Greatsword : public Weapon
{
public:
	Greatsword(const TextureHolder& textures, Category::Type type);
	virtual void flip();
	
private:
	sf::Sprite mSprite;
	bool flipped;
};

