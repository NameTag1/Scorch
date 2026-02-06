#pragma once

#include "Interactable.h"
#include "ChangeableAnimation.h"
#include "Animatable.h"

class NPC : public Interactable, public Animatable
{
public:
	NPC(TextureHolder& textureHolder, json data);

	virtual sf::FloatRect getBoundingRect() const;
	virtual std::vector<unsigned int> getCategory() const;

	virtual void touched(Player_Entity& player);
	virtual void interact(Player_Entity& player);

private:
	virtual void updateCurrent(sf::Time dt, CommandQueue& commands);

	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	Animation mArrow;
	bool mDrawArrow;
	bool mStickyInteract;
};

