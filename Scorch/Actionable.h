#pragma once

#include "Actions.h"
#include "Entity.hpp"

class Actionable
{
public:
	Actionable();
	Actionable(std::vector<Action*> actions);
	void update(sf::Time dt, CommandQueue& Commands, SceneNode& target);
	void pushAction(Action* action);
	void pushAction(std::vector<Action*> actions);
	void removeAction();
	void lock(bool locked);

private:
	int selected;
	std::vector<Action*> mActions;
	std::vector<Action*> mLiveActions; //Live actions, caused by keypresses (moving, attacking, etc.) kept seperate
	bool mLock;
};

