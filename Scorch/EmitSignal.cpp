#include "EmitSignal.h"

#include "Signals.h"

EmitSignal::EmitSignal(Type a, std::string signalName)
	: mSignalName(signalName)
	, Action(a)
{
}

void EmitSignal::update(sf::Time dt, CommandQueue& Commands, SceneNode& target)
{
	Signals::signals.push_back(mSignalName);
}

bool EmitSignal::isFinnished()
{
	return true;
}
