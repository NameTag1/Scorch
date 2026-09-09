#include "MakeAttack.h"

#include "Utility.hpp"

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
	if (mTarget == nullptr) {
		if (Attacker* castedPtr = dynamic_cast<Attacker*>(&target)) {
			mTarget = castedPtr;
		}
		//mTarget = safeCast<Attacker*, SceneNode*>(&target);
	}

	if (mTarget->canAttack()) {
		mTarget->makeAttack(mAttackCode, target);
	}
	if (!mTarget->isAttacking()) {
		mDone = true;
	}
};

bool MakeAttack::isFinnished() {
	return mDone;
};

void MakeAttack::reset() {
	mDone = false;
	mAttackMade = false;
}