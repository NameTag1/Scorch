#include "Interact.h"

#include "Player_Entity.h"

Interact::Interact()
: Action(Action::RunOnce)
{
};

void Interact::update(sf::Time dt, CommandQueue& Commands, SceneNode& target) {
	if (mTarget == nullptr) {
		if (Player_Entity* castedPtr = dynamic_cast<Player_Entity*>(&target)) {
			mTarget = castedPtr;
		}
		//mTarget = safeCast<Player_Entity*, SceneNode*>(&target);
	}
	mTarget->setInteracting(true);
};

bool Interact::isFinnished() {
	return true;
};

void Interact::reset() {

};