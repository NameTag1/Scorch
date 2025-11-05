#include "Actionable.h"
#include <iostream>


Actionable::Actionable()
: selected(0)
, mLock(false)
{

}

Actionable::Actionable(std::vector<Action*> actions)
: selected(0)
, mLock(false)
{
	pushAction(actions);
}

void Actionable::update(sf::Time dt, CommandQueue& Commands, SceneNode& target) {
	for (auto i : mLiveActions) {
		if (i->mType == Action::Live) {
			i->update(dt, Commands, target);
		}
	}
	mLiveActions.clear();

	if (mActions.size() != 0) {
		mActions[selected]->update(dt, Commands, target);

		if (mActions[selected]->isFinnished()) {
			if (mActions[selected]->mType == Action::RunOnce || mActions[selected]->mType == Action::Live) {
				mActions.erase(mActions.begin() + selected);
			}
			else {
				selected++;
			}

			if (selected == mActions.size()) {
				selected = 0;
			}
			mActions[selected]->reset();
		}
	}
	else {
		mLock = false;
	}
};

void Actionable::pushAction(Action* action) {
	if (!mLock) {
		if (action->mType == Action::Live) {
			mLiveActions.push_back(action);
		}
		else {
			mActions.push_back(action);
		}
	}
};

void Actionable::pushAction(std::vector<Action*> actions) {
	if (!mLock) {
		for (auto i : actions) {
			mActions.push_back(i);
		}
	}	
}

void Actionable::removeAction()
{
	for (int i = selected; i < mActions.size();  i++) {
		//mActions[i];
	}
}

void Actionable::lock(bool locked)
{
	mLock = locked;
}
