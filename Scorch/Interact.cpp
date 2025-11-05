#include "Interact.h"

#include "Player_Entity.h"

Interact::Interact()
: Action(Action::RunOnce)
{
};

void Interact::update(sf::Time dt, CommandQueue& Commands, SceneNode& target) {
	Player_Entity* a = dynamic_cast<Player_Entity*>(&target);
	a->setInteracting(true);
};

bool Interact::isFinnished() {
	return true;
};

void Interact::reset() {

};