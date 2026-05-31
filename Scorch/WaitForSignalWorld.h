#pragma once

#include "WorldAction.h"

class WaitForSignalWorld : public WorldAction
{
public:
	WaitForSignalWorld(std::string signalName);
	//virtual void update(sf::Time dt, CommandQueue& Commands, World& target);
	virtual bool isFinnished();

private:
	std::string mSignalName;
};

