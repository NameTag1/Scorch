#include "Player.hpp"
#include "CommandQueue.hpp"
#include "Entity.hpp"
#include "Player_Entity.h"
#include "Platformer.h"

#include "Jump.h"
#include "Lock.h"
#include "MakeAttack.h"
#include "Interact.h"
#include "Move.h"

#include "UseWeapon.h"

#include <map>
#include <string>
#include <algorithm>
#include <iostream>

struct EntityMover
{
	EntityMover(float vx, float vy)
	: velocity(vx, vy)
	{
	}

	void operator() (Entity& entity, sf::Time) const
	{
		entity.accelerate(velocity);
	}

	sf::Vector2f velocity;
};

struct PlatformerMover
{
	PlatformerMover(bool left)
		: left(left)
	{
	}

	void operator() (Platformer& entity, sf::Time) const
	{
		entity.move(left);
	}

	bool left;
};

struct Jumper
{
	Jumper()
	{
	}

	void operator() (Platformer& entity, sf::Time) const
	{
		entity.jump();
	}
};

struct Interacts
{
	Interacts()
	{
	}

	void operator() (Player_Entity& player, sf::Time) const
	{
		player.setInteracting(true);
	}
};

//struct MakeAttack
//{
//	MakeAttack(std::string attackString)
//	{
//		mAttack = attackString;
//	}
//
//	void operator() (Player_Entity& player, sf::Time) const
//	{
//		player.makeAttack(mAttack, player);
//	}
//
//	std::string mAttack;
//};

struct DeployAction
{
	DeployAction(Action* action)
	{
		mAction = action;
	}

	void operator() (Actionable& player, sf::Time) const
	{
		player.pushAction(mAction);
	}

	Action* mAction;
};

Player::Player()
{
	// Set initial key bindings
	mKeyBinding[sf::Keyboard::Left] = MoveLeft;
	mKeyBinding[sf::Keyboard::Right] = MoveRight;
	mKeyBinding[sf::Keyboard::Up] = JumpA;
	mKeyBinding[sf::Keyboard::Down] = MoveDown;
	mKeyBinding[sf::Keyboard::Space] = InteractA;
	mKeyBinding[sf::Keyboard::Num1] = Attack1;
	mKeyBinding[sf::Keyboard::Num2] = Attack2;
	mKeyBinding[sf::Keyboard::Num3] = Attack3;
	mKeyBinding[sf::Keyboard::Num4] = Attack4;

	// Set initial action bindings
	initializeActions();	

	// Assign all categories to player
	for(auto& pair : mActionBinding)
		pair.second.category = Category::Player;
}

void Player::handleEvent(const sf::Event& event, CommandQueue& commands)
{
	if (event.type == sf::Event::KeyPressed)
	{
		// Check if pressed key appears in key binding, trigger command if so
		auto found = mKeyBinding.find(event.key.code);
		if (found != mKeyBinding.end() && !isRealtimeAction(found->second))
			commands.push(mActionBinding[found->second]);
	}
}

void Player::handleRealtimeInput(CommandQueue& commands)
{
	// Traverse all assigned keys and check if they are pressed
	for(auto pair : mKeyBinding)
	{
		// If key is pressed, lookup action and trigger corresponding command
		if (sf::Keyboard::isKeyPressed(pair.first) && isRealtimeAction(pair.second))
			commands.push(mActionBinding[pair.second]);
	}
}

void Player::assignKey(PActions action, sf::Keyboard::Key key)
{
	// Remove all keys that already map to action
	for (auto itr = mKeyBinding.begin(); itr != mKeyBinding.end(); )
	{
		if (itr->second == action)
			mKeyBinding.erase(itr++);
		else
			++itr;
	}

	// Insert new binding
	mKeyBinding[key] = action;
}

sf::Keyboard::Key Player::getAssignedKey(PActions action) const
{
	for(auto pair : mKeyBinding)
	{
		if (pair.second == action)
			return pair.first;
	}

	return sf::Keyboard::Unknown;
}

void Player::initializeActions()
{
	mActionBinding[MoveLeft].action	 = derivedAction<Player_Entity>(DeployAction(new Move(true)));
	mActionBinding[MoveRight].action = derivedAction<Player_Entity>(DeployAction(new Move(false)));
	mActionBinding[MoveDown].action  = derivedAction<Player_Entity>(EntityMover(0.f, 0.f));
	mActionBinding[JumpA].action = derivedAction<Player_Entity>(DeployAction(new Jump()));
	mActionBinding[InteractA].action = derivedAction<Player_Entity>(DeployAction(new Interact()));
	mActionBinding[Attack1].action = derivedAction<Player_Entity>(DeployAction(new UseWeapon("Slot 1")));
	mActionBinding[Attack2].action = derivedAction<Player_Entity>(DeployAction(new UseWeapon("Slot 2")));
	mActionBinding[Attack3].action = derivedAction<Player_Entity>(DeployAction(new UseWeapon("Slot 3")));
	mActionBinding[Attack4].action = derivedAction<Player_Entity>(DeployAction(new UseWeapon("Slot 4")));
}

bool Player::isRealtimeAction(PActions action)
{
	switch (action)
	{
		case MoveLeft:
		case MoveRight:
		case MoveDown:
			return true;

		default:
			return false;
	}
}
