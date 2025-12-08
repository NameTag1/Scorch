#pragma once

#ifndef Player_Entity_h
#define Player_Entity_h

#include "Entity.hpp"
#include "Platformer.h"
#include "Attacker.h"
#include "WeaponWielder.h"
#include "CommandQueue.hpp"
#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.hpp"
#include "Utility.hpp"
#include "Animatable.h"

#include <SFML/Graphics.hpp>

class Player_Entity : public Platformer, public WeaponWielder, public Attacker, public Actionable, public Animatable
{
public:
	Player_Entity();
	Player_Entity(const TextureHolder& textures);
	Player_Entity(const TextureHolder& textures, json data);
	virtual std::vector<unsigned int> getCategory() const;
	virtual sf::FloatRect getBoundingRect() const;
	virtual bool markedForRemoval();
	bool getInteracting();
	void setInteracting(bool interacting);
	static Player_Entity* getInstance();

private:
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const; 
	virtual void updateCurrent(sf::Time dt, CommandQueue& Commands);

private:
	sf::Sprite mSprite;
	bool isAttacking;
	bool isInteracting;
	bool suppressInteracting;
	bool isMarkedForRemoval;
	static Player_Entity* instance;
	//ChangeableAnimation mChangeable;
};

#endif
