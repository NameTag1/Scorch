#pragma once

#include "State.hpp"

class SaveSelectorState : public State
{
public:
	SaveSelectorState(StateStack& stack, Context context);

	virtual void					draw();
	virtual bool					update(sf::Time dt);
	virtual bool					handleEvent(const sf::Event& event);
};