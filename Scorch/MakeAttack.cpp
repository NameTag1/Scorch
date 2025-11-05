#include "MakeAttack.h"
#include "Player_Entity.h"
#include "World.hpp"
#include <iostream>


MakeAttack::MakeAttack(std::string attack)
: mAttackCode(attack)
, mDone(false)
, mAttackMade(false)
, Action(Action::Persistent)
{

}

MakeAttack::MakeAttack(std::string attack, Action::Type runOnce)
: mAttackCode(attack)
, mDone(false)
, mAttackMade(false)
, Action(runOnce)
{
}

void MakeAttack::update(sf::Time dt, CommandQueue& Commands, SceneNode& target)
{
	std::cout << "MAKEATTACK\n";
	Attacker* a = dynamic_cast<Attacker*>(&target);
	if (a->canAttack()) {
		a->makeAttack(mAttackCode, target);
	}
	if (!a->isAttacking()) {
		mDone = true;
	}
	/*if (mAttackMade == false) {
		Entity* entity = dynamic_cast<Entity*>(&target);
		bool left = (entity->lastKnownDirection().x <= 0) ? true : false;
		bool up = (entity->lastKnownDirection().y <= 0) ? true : false;
		Attack* attack = mAttack->clone();
		attack->setDirection(left, up);
		attack->move(entity->getPosition());
		attack->move(attack->getOffset());

		std::array<SceneNode*, LayerCount> i = World::getInstance()->getSceneLayers();
		i[Layer::AttackLayer]->attachChild((std::unique_ptr<SceneNode>) attack);
		mAttackMade = true;
	}
	else {
		mDone = true;
	}*/
};

bool MakeAttack::isFinnished() {
	return mDone;
};

void MakeAttack::reset() {
	mDone = false;
	mAttackMade = false;
}