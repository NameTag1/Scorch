#pragma once

#include "Attack.h"
#include "Actions.h"

class MakeAttack : public Action
{
public:
	MakeAttack(std::string attack);
	MakeAttack(std::string attack, Action::Type runOnce);
	virtual void update(sf::Time dt, CommandQueue& Commands, SceneNode& target);
	virtual bool isFinnished();
	virtual void reset();

private:
	std::string mAttackCode;
	bool mAttackMade;
	sf::Time mCooldown;
	bool mDone;
};

