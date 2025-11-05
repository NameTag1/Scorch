
#include "SettingsState.hpp"
#include "ResourceHolder.hpp"
#include "Utility.hpp"

#include <functional>

#include <SFML/Graphics/RenderWindow.hpp>


SettingsState::SettingsState(StateStack& stack, Context context)
: State(stack, context)
, mGUIContainer()
{
	mGUIContainer.setRelativeRect(RelativeRect(sf::FloatRect(0, 0, 1, 1)));

	mBackgroundSprite.setTexture(context.textures->get(Textures::TitleScreen));
	
	// Build key binding buttons and labels
	addButtonLabel(Player::MoveLeft,  0.1, "Left", context);
	addButtonLabel(Player::MoveRight, 0.175, "Right", context);
	addButtonLabel(Player::MoveDown, 0.25, "Down", context);
	addButtonLabel(Player::JumpA, 0.325, "Up", context);
	addButtonLabel(Player::InteractA, 0.4, "Interact", context);
	addButtonLabel(Player::Attack1, 0.475, "Attack 1", context);
	addButtonLabel(Player::Attack2, 0.55, "Attack 2", context);
	addButtonLabel(Player::Attack3, 0.625, "Attack 3", context);
	addButtonLabel(Player::Attack4, 0.7, "Attack 4", context);

	updateLabels();

	auto backButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
	backButton->setRelativeRect(RelativeRect(sf::FloatRect(0.7, 0.85, 0.2, 0.075)));
	backButton->setText("Back");
	backButton->setCallback(std::bind(&SettingsState::requestStackPop, this));

	mGUIContainer.pack(backButton);
}

void SettingsState::draw()
{
	sf::RenderWindow& window = *getContext().window;

	window.draw(mBackgroundSprite);
	window.draw(mGUIContainer);
}

bool SettingsState::update(sf::Time)
{
	sf::RenderWindow& window = *getContext().window;
	mGUIContainer.updateRect(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));
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
	mBindingButtons[action]->setRelativeRect(RelativeRect(sf::FloatRect(0.1, y, 0.2,0.075)));
	mBindingButtons[action]->setText(text);
	mBindingButtons[action]->setToggle(true);

	mBindingLabels[action] = std::make_shared<GUI::Label>("", *context.fonts);
	mBindingLabels[action]->setRelativeRect(RelativeRect(sf::FloatRect(0.32, y, 0.05,0.075)));

	mGUIContainer.pack(mBindingButtons[action]);
	mGUIContainer.pack(mBindingLabels[action]);
}
