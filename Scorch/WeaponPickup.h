#pragma once

#include "SceneNode.hpp"
#include "Interactable.h"
#include "Animation.h"
#include "DataRetrivalTypes.h"
#include "DataTable.h"

class WeaponPickup : public Interactable
{
public:
	WeaponPickup(TextureHolder& textureHolder, Weapon* weapon, json data);
	void setBounds(sf::IntRect newBounds);
	virtual sf::FloatRect getBoundingRect() const;
	virtual std::vector<unsigned int> getCategory() const;

	virtual bool isMarkedForRemoval() const;

	virtual void interact(Player_Entity& player);

private:
	virtual void updateCurrent(sf::Time dt, CommandQueue& commands);

	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	bool mUsed;
	Weapon* mChild;
	sf::Sprite mSprite;
};

