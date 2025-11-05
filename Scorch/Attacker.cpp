#include "Attacker.h"
#include "World.hpp"
#include <iostream>

Attacker::Attacker()
: mCooldown(sf::seconds(0))
, mAttacking(sf::seconds(0))
{
}

Attacker::Attacker(std::map<std::string, Attack*>& attacks)
: Attacker()
{
	pushAttack(attacks);
};

void Attacker::update(sf::Time dt, CommandQueue& Commands, SceneNode& target) {
	mCooldown -= dt;
	mAttacking -= dt;
};

void Attacker::clearAttacks()
{
	mAttacks.clear();
}

void Attacker::pushAttack(std::string a, Attack* attack) {
	mAttacks[a] = attack;
};

void Attacker::pushAttack(std::map<std::string, Attack*> attacks) {
	for (auto i : attacks) {
		mAttacks[i.first] = i.second;
	}
}

void Attacker::makeAttack(std::string selectedAttack, SceneNode& target)
{
	//Actionable::pushAction(*new MakeAttackA(*mAttacks[selectedAttack]->clone()));
	
	if (mAttacks[selectedAttack] == nullptr) {
		return;
	}

	Entity* entity = dynamic_cast<Entity*>(&target);
	bool left = (entity->lastKnownDirection().x <= 0) ? true : false;
	bool up = (entity->lastKnownDirection().y <= 0) ? true : false;
	if (canAttack()) {
		mCooldown = sf::seconds(0);
		mCooldown += mAttacks[selectedAttack]->getCooldown();
		mAttacking = sf::seconds(0);
		mAttacking += mAttacks[selectedAttack]->getDuration();
		Attack* a = mAttacks[selectedAttack]->clone();
		a->setDirection(left, up);
		if (a->getIndependent()) {
			a->move(a->getOffset());
			a->move(entity->getWorldPosition());
			Scene_Builder::getInstance()->getLayers()[AttackLayer]->attachChild((std::unique_ptr<SceneNode>) a);
		}
		else {
			a->move(a->getOffset());
			entity->attachChild((std::unique_ptr<SceneNode>) a);
		}
	}
	/*if (canAttack()) {
		mCooldown = sf::seconds(0);
		mCooldown += mAttacks[selectedAttack]->getCooldown();
		mAttacking = sf::seconds(0);
		mAttacking += mAttacks[selectedAttack]->getDuration();
		Action* a = new MakeAttackA(*mAttacks[selectedAttack]);
		Actionable::livePushAction(*a);
	}*/
}

bool Attacker::canAttack()
{
	return mCooldown <= sf::seconds(0);
}

bool Attacker::isAttacking()
{
	return mAttacking <= sf::seconds(0);
}