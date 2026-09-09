#pragma once

#include "Action.h"

class EmitSignal : public Action
{
public:
	EmitSignal(Type a, std::string signalName);
	virtual void update(sf::Time dt, CommandQueue& Commands, SceneNode& target);
	virtual bool isFinnished();

private:
	std::string mSignalName;
};