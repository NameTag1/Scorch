#include "Action.h"

Action::Action(Type type)
	: mType(type)
{
}

void Action::update(sf::Time dt, CommandQueue& Commands, SceneNode& Target) {

};

bool Action::isFinnished() {
	return false;
};

void Action::reset() {

}