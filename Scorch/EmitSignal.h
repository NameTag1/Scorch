#pragma once

#include "Actions.h"

class EmitSignal : public Action
{
public:
	EmitSignal(Type a, std::string signalName);
	virtual void update(sf::Time dt, CommandQueue& Commands, SceneNode& target);
	virtual bool isFinnished();

private:
	std::string mSignalName;
};

