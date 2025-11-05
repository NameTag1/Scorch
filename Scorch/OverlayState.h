#pragma once

#include "State.hpp"
#include "Container.hpp"
#include "Label.hpp"
#include "Bar.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include "Image.h"


class OverlayState : public State
{
public:
	OverlayState(StateStack& stack, Context context);

	virtual void		draw();
	virtual bool		update(sf::Time dt);
	virtual bool		handleEvent(const sf::Event& event);


private:
	sf::Sprite			mBackgroundSprite;
	GUI::Label*			mHealthText;
	GUI::Bar*			mHealthBar;
	std::vector<GUI::Image*> mWeapons;
	GUI::Container 		mGUIContainer;
	GUI::Container 		mPlayerGUIContainer;
	Context				mSavedContext;
};