
#include "TitleState.hpp"
#include "ResourceHolder.hpp"
#include "Utility.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>
#include "Image.h"
#include "Label.hpp"


TitleState::TitleState(StateStack& stack, Context context)
: State(stack, context)
, mGUIContainer()
{
	mGUIContainer.setRelativeRect(RelativeRect(sf::FloatRect(0, 0, 1, 1)));

	auto background = std::make_shared<GUI::Image>(*context.textures, Textures::TitleScreen);
	background->setRelativeRect(RelativeRect(sf::FloatRect(0, 0, 1, 1)));

	auto title = std::make_shared<GUI::Label>("Scorch\nClick anywhere to start", *context.fonts);
	title->setRelativeRect(RelativeRect(sf::FloatRect(0.5, 0.5, 0.2, 0.2)));

	mGUIContainer.pack(background);
	mGUIContainer.pack(title);
}

void TitleState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	window.draw(mGUIContainer);
}

bool TitleState::update(sf::Time dt)
{
	sf::RenderWindow& window = *getContext().window;
	mGUIContainer.updateRect(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));

	return true;
}

bool TitleState::handleEvent(const sf::Event& event)
{
	// If any key is pressed, trigger the next screen
	if (event.type == sf::Event::KeyReleased || event.type == sf::Event::MouseButtonReleased)
	{
		requestStackPop();
		requestStackPush(States::Menu);
	}

	return true;
}