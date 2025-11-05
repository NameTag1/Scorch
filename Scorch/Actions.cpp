#include "Actions.h"
#include <iostream>
#include "With.h"

Action::Action(Type type)
: mType(type)
{
}

void Action::update(sf::Time dt, CommandQueue& Commands, SceneNode& target) {
	
};

bool Action::isFinnished() {
	return false;
};

void Action::reset() {

}