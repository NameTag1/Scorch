#pragma once

#include <map>

#include "ResourceIdentifiers.hpp"
#include "SceneNode.hpp"
#include "Attack.h"
#include "Actions.h"
#include "Interactable.h"

class Weapon : public Interactable
{
public:
	Weapon(const TextureHolder& textures, Category::Type type);
	virtual void updateCurrent(sf::Time dt, CommandQueue& commands);
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	
	virtual void update(sf::Time dt, CommandQueue& Commands, SceneNode& target);
	void setDirection(bool left, bool up);
	virtual void flip();

	virtual void interact(Player_Entity& player);
	virtual void useWeapon(std::string selectedAttack, SceneNode& target);
	Textures::ID getIcon();

	virtual std::vector<unsigned int> getCategory() const;

	std::map<std::string, Action*> getActions();
	std::map<std::string, Attack*> getAttacks();

protected:
	std::map<std::string, Action*> mActions; //MakeAttack and movement actions
	std::map<std::string, Attack*> mAttacks;
	bool left;
	bool up;
	Textures::ID mIcon;
};

