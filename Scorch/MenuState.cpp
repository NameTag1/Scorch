
#include "ResourceHolder.hpp"
#include "MenuState.hpp"
#include "Button.hpp"

#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>
#include "Image.h"

MenuState::MenuState(StateStack& stack, Context context)
: State(stack, context)
, mGUIContainer()
{
	mGUIContainer.setRelativeRect(RelativeRect(sf::FloatRect(0,0,1,1)));

	auto background = std::make_shared<GUI::Image>(*context.textures, Textures::TitleScreen);
	background->setRelativeRect(RelativeRect(sf::FloatRect(0, 0, 1, 1)));

	auto playButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
	playButton->setRelativeRect(RelativeRect(sf::FloatRect(0, 0, 0.2, 0.075)));
	playButton->setText("Play");
	playButton->setCallback([this] ()
	{
		requestStackPop();
		requestStackPush(States::Game);
		requestStackPush(States::Overlay);
	});

	auto settingsButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
	settingsButton->setRelativeRect(RelativeRect(sf::FloatRect(0.5, 0.5, 0.2, 0.075), RelativeWH::Normal, Anchor::Center));
	settingsButton->setText("Settings");
	settingsButton->setCallback([this] ()
	{
		requestStackPush(States::Settings);
	});

	auto exitButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
	exitButton->setRelativeRect(RelativeRect(sf::FloatRect(1, 1, 0.2, 0.075), RelativeWH::Normal, Anchor::BR));
	exitButton->setText("Exit");
	exitButton->setCallback([this] ()
	{
		requestStackPop();
	});

	mGUIContainer.pack(background);
	mGUIContainer.pack(playButton);
	mGUIContainer.pack(settingsButton);
	mGUIContainer.pack(exitButton);
}

void MenuState::draw()
{
	sf::RenderWindow& window = *getContext().window;

	sf::View mView(sf::FloatRect(0,0,window.getSize().x, window.getSize().y));
	window.setView(mView); 

	window.draw(mGUIContainer);
}

bool MenuState::update(sf::Time)
{
	sf::RenderWindow& window = *getContext().window;
	mGUIContainer.updateRect(sf::FloatRect(0,0, window.getSize().x, window.getSize().y));
	return true;
}

bool MenuState::handleEvent(const sf::Event& event)
{
	mGUIContainer.handleEvent(event);
	return false;
}
