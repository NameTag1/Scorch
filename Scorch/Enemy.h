#pragma once

#include "Platformer.h"
#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.hpp"
#include "Actionable.h"
#include "Attacker.h"

class Enemy : public Platformer, public Attacker, public Actionable
{
public:
	Enemy(const TextureHolder& textures);
	virtual std::vector<unsigned int> getCategory() const;
	virtual sf::FloatRect getBoundingRect() const;
	virtual bool markedForRemoval();

private:
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void updateCurrent(sf::Time dt, CommandQueue& Commands);

private:
	sf::Sprite mSprite;
	bool isAttacking;
	bool isMarkedForRemoval;
};

