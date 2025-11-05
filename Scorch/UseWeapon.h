#pragma once

#include "Actions.h"

class UseWeapon : public Action
{
public:
	UseWeapon(std::string action);
	UseWeapon(std::string action, Action::Type RunOnce); 
	virtual void update(sf::Time dt, CommandQueue& Commands, SceneNode& target);
	virtual bool isFinnished();
	virtual void reset();

private:
	std::string mString;
};

