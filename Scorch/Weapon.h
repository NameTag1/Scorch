#pragma once

#include "ResourceIdentifiers.hpp"
#include "SceneNode.hpp"
#include "Attack.h"
#include "Action.h"
#include "Interactable.h"

class Weapon
{
public:
	Weapon(const TextureHolder& textures, Category::Type type);
	
	virtual void update(sf::Time dt, CommandQueue& Commands, SceneNode& target);
	void setDirection(bool left, bool up);
	virtual void flip();

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

