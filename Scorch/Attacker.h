#pragma once

#include <map>
#include "Actionable.h"
#include "Actions.h"
#include "Entity.hpp"
#include "Attack.h"
#include "MakeAttack.h"

class Attacker
{
public:
	Attacker();
	Attacker(std::map<std::string, Attack*>& attacks);
	void update(sf::Time dt, CommandQueue& Commands, SceneNode& target);

	void clearAttacks();
	void pushAttack(std::string s, Attack* attack);
	void pushAttack(std::map<std::string, Attack*> attacks);

	virtual void makeAttack(std::string selectedAttack, SceneNode& target);
	bool canAttack();
	bool isAttacking();

private:
	sf::Time mAttacking;
	sf::Time mCooldown;
	double mDamageModifier;
	std::map<std::string, Attack*> mAttacks;
};

