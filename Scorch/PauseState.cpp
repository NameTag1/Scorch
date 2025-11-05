
#include "PauseState.hpp"
#include "Button.hpp"
#include "Label.hpp"
#include "ResourceHolder.hpp"
#include "Utility.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <iostream>
#include "Player_Entity.h"


PauseState::PauseState(StateStack& stack, Context context)
: State(stack, context)
, mBackgroundSprite()
, mGUIContainer()
, mSavedContext(context)
{
	mGUIContainer.setRelativeRect(RelativeRect(sf::FloatRect(0, 0, 1, 1)));

	sf::Font& font = context.fonts->get(Fonts::Main);
	sf::Vector2f windowSize(context.window->getSize());

	Player_Entity* player = Player_Entity::getInstance();

	auto returnButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
	returnButton->setRelativeRect(RelativeRect(sf::FloatRect(0.5f, 0.5f, 0.2f, 0.075f), RelativeWH::Normal, Anchor::BL));
	returnButton->setText("Return");
	returnButton->setCallback([this] ()
	{
		requestStackPop();
	});

	auto backToMenuButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
	backToMenuButton->setRelativeRect(RelativeRect(sf::FloatRect(0.5f,0.5f,0.2f,0.075f), RelativeWH::Normal, Anchor::TL));
	backToMenuButton->setText("Back to menu");
	backToMenuButton->setCallback([this] ()
	{
		requestStateClear();
		requestStackPush(States::Menu);
	});

	mGUIContainer.pack(returnButton);
	mGUIContainer.pack(backToMenuButton);


	auto HealthText = std::make_shared<GUI::Label>("Health: " + std::to_string(player->getHitpoints()), *context.fonts);
	HealthText->setRelativeRect(RelativeRect(sf::FloatRect(0.4f, 0.5f, 0.1f, 0.075f), RelativeWH::Normal, Anchor::Center));

	mGUIContainer.pack(HealthText);
}

void PauseState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	//window.setView(window.getDefaultView());

	sf::RectangleShape backgroundShape;
	backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
	backgroundShape.setSize(window.getView().getSize());
	
	//sf::RenderWindow& window = *getContext().window;

	sf::View mView(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));
	//std::cout << window.getSize().x << " - " <<  mView.getSize().x << "\n";
	window.setView(mView);

	window.draw(mBackgroundSprite);
	window.draw(mGUIContainer);
	window.draw(backgroundShape);
	window.draw(mGUIContainer);
}

bool PauseState::update(sf::Time)
{
	sf::RenderWindow& window = *getContext().window;
	mGUIContainer.updateRect(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));
	return false;
}

bool PauseState::handleEvent(const sf::Event& event)
{
	mGUIContainer.handleEvent(event);
	return false;
}