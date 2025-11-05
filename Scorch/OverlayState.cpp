#include "OverlayState.h"

#include "Button.hpp"
#include "Label.hpp"
#include "ResourceHolder.hpp"
#include "Utility.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <iostream>
#include "Player_Entity.h"
#include "Image.h"


OverlayState::OverlayState(StateStack& stack, Context context)
	: State(stack, context)
	, mBackgroundSprite()
	, mGUIContainer()
	, mPlayerGUIContainer()
	, mSavedContext(context)
{
	context.textures->load(Textures::Greatsword, "resources/Greatsword.bmp");
	context.textures->load(Textures::Default, "resources/Default.bmp");

	mGUIContainer.setRelativeRect(RelativeRect(sf::FloatRect(0, 0, 0.25f, 0.15f), RelativeWH::WHBased, Anchor::TL));

	sf::Font& font = context.fonts->get(Fonts::Main);
	sf::Vector2f windowSize(context.window->getSize());

	Player_Entity* player = Player_Entity::getInstance();

	auto background = std::make_shared<GUI::Image>(*context.textures, Textures::Black);
	background->setRelativeRect(RelativeRect(sf::FloatRect(0.f, 0.f, 1.f, 1.f), RelativeWH::Normal, Anchor::TL));

	auto pauseButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
	pauseButton->setRelativeRect(RelativeRect(sf::FloatRect(0.f, 0.f, 0.2f, 0.2f), RelativeWH::WBased, Anchor::TL));
	pauseButton->setText("||");
	pauseButton->setCallback([this]()
		{
			requestStackPush(States::Pause);
		});

	mGUIContainer.pack(background);
	mGUIContainer.pack(pauseButton);

	int i = 0;
	for (Textures::ID x : player->weaponIcons()) {
		std::cout << i << " " << x << "\n";
		auto weapon = std::make_shared<GUI::Image>(*context.textures, x);
		weapon->setRelativeRect(RelativeRect(sf::FloatRect(0.3f + 0.2f*i, 0.1f, 0.15f, 0.15f), RelativeWH::WBased, Anchor::TL));
		mWeapons.push_back(weapon.get());
		mGUIContainer.pack(weapon);
		i++;
	}

	auto HealthText = std::make_shared<GUI::Label>("Health: " + std::to_string(player->getHitpoints()), *context.fonts);
	mHealthText = HealthText.get(); //Pointer in state so it can be updated
	HealthText->setRelativeRect(RelativeRect(sf::FloatRect(0.4f, 0.5f, 0.1f, 0.075f), RelativeWH::Normal, Anchor::Center));

	auto HealthBar = std::make_shared<GUI::Bar>();
	mHealthBar = HealthBar.get();
	HealthBar->setRelativeRect(RelativeRect(sf::FloatRect(0.5f, 0.8f, 0.6f, 0.075f), RelativeWH::Normal, Anchor::Center));

	mGUIContainer.pack(HealthText);
	mGUIContainer.pack(HealthBar);
}

void OverlayState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	//window.setView(window.getDefaultView());

	//sf::RenderWindow& window = *getContext().window;

	sf::View mView(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));
	//std::cout << window.getSize().x << " - " <<  mView.getSize().x << "\n";
	window.setView(mView);

	window.draw(mBackgroundSprite);
	window.draw(mGUIContainer);
	window.draw(mGUIContainer);
	window.draw(mPlayerGUIContainer);
}

bool OverlayState::update(sf::Time)
{
	sf::RenderWindow& window = *getContext().window;
	mGUIContainer.updateRect(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));

	Player_Entity* player = Player_Entity::getInstance();
	mHealthText->setText("Health: " + std::to_string(player->getHitpoints()));
	mHealthBar->setMessure(50, player->getHitpoints());

	for (int i = 0; i < mWeapons.size();  i++) {
		mWeapons[i]->updateImage(*getContext().textures, player->weaponIcons()[i]);
	}

	return true;
}

bool OverlayState::handleEvent(const sf::Event& event)
{
	if(event.type == sf::Event::MouseMoved || event.type == sf::Event::MouseButtonPressed || event.type == sf::Event::MouseButtonReleased)
		mGUIContainer.handleEvent(event);
	return true;
}