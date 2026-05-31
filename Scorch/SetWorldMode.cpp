#include "SetWorldMode.h"

SetWorldMode::SetWorldMode(World::World_Mode mode) {
	mMode = mode;
}

void SetWorldMode::update(sf::Time dt, CommandQueue& Commands, World& target)
{
	target.setWorldMode(mMode);
}

bool SetWorldMode::isFinnished()
{
	return true;
}
