#pragma once

#include "State.hpp"
#include "Container.hpp"
#include "Label.hpp"
#include "Bar.h"

#include "Entity.hpp"

class BossOverlayState : public State
{
public:
	BossOverlayState(StateStack& stack, Context context);

	static BossOverlayState* getInstance(StateStack& stack, Context context);

	void 				addBoss(Entity* boss);

	virtual void		draw();
	virtual bool		update(sf::Time dt);
	virtual bool		handleEvent(const sf::Event& event);

private:
	static BossOverlayState* mInstance;

	GUI::Container 		mGUIContainer;
	std::map<Entity*, GUI::Bar*> mBossHealthbars;
};

