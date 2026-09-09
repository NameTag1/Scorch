#include "Player.hpp"
#include "CommandQueue.hpp"
#include "Entity.hpp"
#include "Player_Entity.h"
#include "Platformer.h"
#include "PlatformerMovementSuite.h"

#include "Jump.h"
#include "Lock.h"
#include "MakeAttack.h"
#include "Interact.h"
#include "Move.h"
#include "Dash.h"

#include "UseWeapon.h"
#include "ChangeWeapon.h"

#include <map>
#include <string>
#include <algorithm>

struct PlatformerMover
{
	PlatformerMover(float vx, float vy)
	: velocity(vx, vy)
	{
	}

	void operator() (PlatformerMovementSuite& target, sf::Time) const
	{
		target.accelerate(velocity);
	}

	sf::Vector2f velocity;
};

//struct PlatformerMover
//{
//	PlatformerMover(bool running, bool left)
//		: running(running)
//		, left(left)
//	{
//	}
//
//	void operator() (Platformer& entity, sf::Time) const
//	{
//		entity.move(running, left);
//	}
//
//	bool running;
//	bool left;
//};

struct Jumper
{
	Jumper()
	{
	}

	void operator() (PlatformerMovementSuite& target, sf::Time) const
	{
		target.jump();
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
	: mLockAction(false)
{
	// Set initial key bindings
	mKeyBinding[sf::Keyboard::Left] = Left;
	mKeyBinding[sf::Keyboard::Right] = Right;
	mKeyBinding[sf::Keyboard::Up] = JumpA;
	mKeyBinding[sf::Keyboard::Down] = Down;
	mKeyBinding[sf::Keyboard::F] = DashA;
	mKeyBinding[sf::Keyboard::Q] = SwitchL;
	mKeyBinding[sf::Keyboard::E] = SwitchR;
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
	if (event.type == sf::Event::KeyPressed && !mLockAction)
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
		if (sf::Keyboard::isKeyPressed(pair.first) && isRealtimeAction(pair.second) && !mLockAction)
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

void Player::LockActions(bool lock)
{
	mLockAction = lock;
}

void Player::initializeActions()
{
	mActionBinding[Left].action	 = derivedAction<Player_Entity>(DeployAction(new Move(true, true)));
	mActionBinding[Right].action = derivedAction<Player_Entity>(DeployAction(new Move(true, false)));
	mActionBinding[Down].action  = derivedAction<Player_Entity>(PlatformerMover(0.f, 0.f));
	mActionBinding[JumpA].action = derivedAction<Player_Entity>(DeployAction(new Jump()));
	mActionBinding[DashA].action = derivedAction<Player_Entity>(DeployAction(new Dash()));
	mActionBinding[SwitchL].action = derivedAction<Player_Entity>(DeployAction(new ChangeWeapon(-1)));
	mActionBinding[SwitchR].action = derivedAction<Player_Entity>(DeployAction(new ChangeWeapon(1)));
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
		case Left:
		case Right:
		case Down:
			return true;

		default:
			return false;
	}
}
