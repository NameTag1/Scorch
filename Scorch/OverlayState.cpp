#include "OverlayState.h"

#include "Button.hpp"
#include "Label.hpp"
#include "ResourceHolder.hpp"
#include "Utility.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include "Player_Entity.h"
#include "Image.h"


OverlayState::OverlayState(StateStack& stack, Context context)
	: State(stack, context)
	, mBackgroundSprite()
	, mGUIContainer()
	, mPlayerWeaponGUIContainer()
	, mSavedContext(context)
{
	context.textures->load(Textures::Greatsword, "resources/Greatsword.bmp");
	context.textures->load(Textures::Default, "resources/Default.bmp");

	mGUIContainer.setRelativeRect(RelativeRect(sf::FloatRect(0, 0, 0.25f, 0.15f), RelativeWH::WHBased, Anchor::TL));
	mPlayerWeaponGUIContainer.setRelativeRect(RelativeRect(sf::FloatRect(0, 0, 0.25f, 0.15f), RelativeWH::WHBased, Anchor::TL));

	sf::Font& font = context.fonts->get(Fonts::Main);
	sf::Vector2f windowSize(context.window->getSize());

	// Don't cache player or build weapon widgets here: player may not exist yet.
	// Player_Entity* player = Player_Entity::getInstance();

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

	// Don't create weapon image widgets yet; they will be created lazily in update() once a real player exists.

	auto HealthText = std::make_shared<GUI::Label>("Health: 0", *context.fonts);
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
	sf::View mView(sf::FloatRect(0, 0, float(window.getSize().x), float(window.getSize().y)));
	window.setView(mView);

	window.draw(mBackgroundSprite);
	window.draw(mGUIContainer);
	window.draw(mPlayerWeaponGUIContainer);
}

bool OverlayState::update(sf::Time)
{
	sf::RenderWindow& window = *getContext().window;
	mGUIContainer.updateRect(sf::FloatRect(0, 0, float(window.getSize().x), float(window.getSize().y)));
	mPlayerWeaponGUIContainer.updateRect(sf::FloatRect(0, 0, float(window.getSize().x), float(window.getSize().y)));

	Player_Entity* player = Player_Entity::getInstance();
	if (!player) return true; // player not ready yet

	// Lazy-create weapon widgets exactly once, when player becomes available
	if (mWeapons.empty() && !player->weaponIcons().empty()) {
		auto icons = player->weaponIcons();
		int i = 0;
		for (Textures::ID x : icons) {
			auto weapon = std::make_shared<GUI::Image>(*getContext().textures, x);
			weapon->setRelativeRect(RelativeRect(sf::FloatRect(0.3f + 0.2f * i, 0.1f, 0.15f, 0.15f), RelativeWH::WBased, Anchor::TL));
			mPlayerWeaponGUIContainer.pack(weapon);
			mWeapons.push_back(weapon.get());
			++i;
		}
	}

	mHealthText->setText("Health: " + std::to_string(player->getHitpoints()));
	mHealthBar->setMessure(50.f, float(player->getHitpoints()));

	// update existing icons safely
	auto icons = player->weaponIcons();
	const std::size_t count = std::min(mWeapons.size(), icons.size());
	for (std::size_t i = 0; i < count; ++i) {
		if (mWeapons[i]) {
			mWeapons[i]->updateImage(*getContext().textures, icons[i]);
		}
	}

	return true;
}

bool OverlayState::handleEvent(const sf::Event& event)
{
	if(event.type == sf::Event::MouseMoved || event.type == sf::Event::MouseButtonPressed || event.type == sf::Event::MouseButtonReleased)
		mGUIContainer.handleEvent(event);
	return true;
}