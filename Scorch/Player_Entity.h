#pragma once

#ifndef Player_Entity_h
#define Player_Entity_h

#include "Entity.hpp"
#include "PlatformerMovementSuite.h"
#include "Attacker.h"
#include "Actionable.h"
#include "WeaponWielder.h"
#include "CommandQueue.hpp"
#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.hpp"
#include "Utility.hpp"
#include "Animatable.h"

#include <SFML/Graphics.hpp>

class Player_Entity : public PlatformerMovementSuite, public Entity, public WeaponWielder, public Attacker, public Actionable, public Animatable
{
public:
	enum playerState {
		grounded,
		drifting, //When applying acceleration one way, but moving the other bc of inertia
		running,
		walking,
		jumping,
		falling,
		climbing, //When climbing walls
		ledge //Clinging to the edge of a surface
	};

public:
	Player_Entity(const TextureHolder& textures, json data);
	virtual std::vector<unsigned int> getCategory() const;
	virtual sf::FloatRect getBoundingRect() const;
	
	virtual bool isMarkedForRemoval() const;
	virtual bool isDestroyed() const;

	//void leftPressed();
	//void rightPressed();
	//void upPressed();
	//void downPressed();
	//void dashPressed();
	//void slot1Pressed();
	//void slot2Pressed();
	//void slot3Pressed();
	
	bool getInteracting();
	void setInteracting(bool interacting);
	static Player_Entity* getInstance();
	static void resetInstance();

	playerState getPlayerState() const;


private:
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const; 
	virtual void updateCurrent(sf::Time dt, CommandQueue& Commands);

private:
	bool isAttacking;
	bool isInteracting;
	static Player_Entity* instance;

	playerState mPlayerState;
};

#endif
