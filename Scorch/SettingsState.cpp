
#include "SettingsState.hpp"
#include "ResourceHolder.hpp"
#include "Utility.hpp"

#include <functional>

#include <SFML/Graphics/RenderWindow.hpp>
#include "Player.hpp"
#include "Image.h"


SettingsState::SettingsState(StateStack& stack, Context context)
: State(stack, context)
, mGUIContainer()
{
	mGUIContainer.setRelativeRect(RelativeRect(sf::FloatRect(0, 0, 1, 1)));
	
	auto background = std::make_shared<GUI::Image>(*context.textures, Textures::TitleScreen);
	background->setRelativeRect(RelativeRect(sf::FloatRect(0, 0, 1, 1)));
	
	// Build key binding buttons and labels
	addButtonLabel(Player::MoveLeft,  0.1f, "Left", context);
	addButtonLabel(Player::MoveRight, 0.175f, "Right", context);
	addButtonLabel(Player::MoveDown, 0.25f, "Down", context);
	addButtonLabel(Player::JumpA, 0.325f, "Up", context);
	addButtonLabel(Player::InteractA, 0.4f, "Interact", context);

	addButtonLabel(Player::SwitchL, 0.475f, "Switch Weapon Left", context);
	addButtonLabel(Player::SwitchR, 0.55f, "Switch Weapon Right", context);
	addButtonLabel(Player::Attack1, 0.625f, "Attack 1", context);
	addButtonLabel(Player::Attack2, 0.7f, "Attack 2", context);
	addButtonLabel(Player::Attack3, 0.775f, "Attack 3", context);
	addButtonLabel(Player::Attack4, 0.85f, "Attack 4", context);

	updateLabels();

	auto backButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
	backButton->setRelativeRect(RelativeRect(sf::FloatRect(0.7f, 0.85f, 0.2f, 0.075f)));
	backButton->setText("Back");
	backButton->setCallback(std::bind(&SettingsState::requestStackPop, this));

	mGUIContainer.pack(background);
	mGUIContainer.pack(backButton);
}

void SettingsState::draw()
{
	sf::RenderWindow& window = *getContext().window;

	window.draw(mGUIContainer);
}

bool SettingsState::update(sf::Time)
{
	sf::RenderWindow& window = *getContext().window;
	mGUIContainer.updateRect(sf::FloatRect(0, 0, float(window.getSize().x), float(window.getSize().y)));
	return true;
}

bool SettingsState::handleEvent(const sf::Event& event)
{
	bool isKeyBinding = false;
	
	// Iterate through all key binding buttons to see if they are being pressed, waiting for the user to enter a key
	for (std::size_t action = 0; action < Player::ActionCount; ++action)
	{
		if (mBindingButtons[action]->isActive())
		{
			isKeyBinding = true;
			if (event.type == sf::Event::KeyReleased)
			{
				getContext().player->assignKey(static_cast<Player::PActions>(action), event.key.code);
				mBindingButtons[action]->deactivate();
			}
			break;
		}
	}

	// If pressed button changed key bindings, update labels; otherwise consider other buttons in container
	if (isKeyBinding)
		updateLabels();
	else
		mGUIContainer.handleEvent(event);

	return false;
}

void SettingsState::updateLabels()
{
	Player& player = *getContext().player;

	for (std::size_t i = 0; i < Player::ActionCount; ++i)
	{
		sf::Keyboard::Key key = player.getAssignedKey(static_cast<Player::PActions>(i));
		mBindingLabels[i]->setText(toString(key));
	}
}

void SettingsState::addButtonLabel(Player::PActions action, float y, const std::string& text, Context context)
{
	mBindingButtons[action] = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
	mBindingButtons[action]->setRelativeRect(RelativeRect(sf::FloatRect(0.1f, y, 0.2f, 0.075f)));
	mBindingButtons[action]->setText(text);
	mBindingButtons[action]->setToggle(true);

	mBindingLabels[action] = std::make_shared<GUI::Label>("", *context.fonts);
	mBindingLabels[action]->setRelativeRect(RelativeRect(sf::FloatRect(0.32f, y, 0.05f,0.075f)));

	mGUIContainer.pack(mBindingButtons[action]);
	mGUIContainer.pack(mBindingLabels[action]);
}
