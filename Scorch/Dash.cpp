#include "Dash.h"

#include "Logger.h"

Dash::Dash()
: Action(Action::RunOnce)
{
}

void Dash::update(sf::Time dt, CommandQueue& Commands, SceneNode& target)
{
	Platformer* platformer = dynamic_cast<Platformer*>(&target);
	if(platformer->lastKnownAcceleration().x > 0) {
		platformer->dash(false); // Dash to the right
	}
	else if(platformer->lastKnownAcceleration().x < 0) {
		platformer->dash(true); // Dash to the left
	}
};

bool Dash::isFinnished() {
	return true;
};

void Dash::reset() {
}