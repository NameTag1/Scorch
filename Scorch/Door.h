#pragma once

#include "SceneNode.hpp"
#include "Interactable.h"
#include "Animation.h"
#include "DataRetrivalTypes.h"
#include "DataTable.h"

class Door : public Interactable
{
public:
	Door(TextureHolder& textureHolder, DataRetrivalType::Doors type, Scenes scene);
	void setBounds(sf::IntRect newBounds);
	virtual sf::FloatRect getBoundingRect() const;
	virtual std::vector<unsigned int> getCategory() const;
	Scenes getScene() const;
	sf::Vector2f getPlayerPos() const;

	virtual void interact(Player_Entity& player);

private:
	virtual void updateCurrent(sf::Time dt, CommandQueue& commands);

	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	Scenes mScene;
	sf::Sprite mSprite;
	Animation mArrow;
	sf::Vector2f mPlayerPos;
};
