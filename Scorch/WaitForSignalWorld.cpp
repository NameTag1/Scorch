#include "WaitForSignalWorld.h"

#include "Signals.h"

WaitForSignalWorld::WaitForSignalWorld(std::string signalName)
	: mSignalName(signalName)
{
}

bool WaitForSignalWorld::isFinnished()
{
	for (auto i : Signals::signals) {
		if (i == mSignalName) {
			Signals::signals.clear();
			return true;
		}
	}
	return false;
}
