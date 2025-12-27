#include "SaveSelectorState.h"

SaveSelectorState::SaveSelectorState(StateStack& stack, Context context)
	: State(stack, context)
{
}

void SaveSelectorState::draw()
{
	/*sf::RenderWindow& window = *getContext().window;

	window.draw(mBackgroundSprite);
	window.draw(mGUIContainer);*/
}

bool SaveSelectorState::update(sf::Time)
{
	/*sf::RenderWindow& window = *getContext().window;
	mGUIContainer.updateRect(sf::FloatRect(0, 0, float(window.getSize().x), float(window.getSize().y)));
	return true;*/
}

bool SaveSelectorState::handleEvent(const sf::Event& event)
{
	//bool isKeyBinding = false;

	//// Iterate through all key binding buttons to see if they are being pressed, waiting for the user to enter a key
	//for (std::size_t action = 0; action < Player::ActionCount; ++action)
	//{
	//	if (mBindingButtons[action]->isActive())
	//	{
	//		isKeyBinding = true;
	//		if (event.type == sf::Event::KeyReleased)
	//		{
	//			getContext().player->assignKey(static_cast<Player::PActions>(action), event.key.code);
	//			mBindingButtons[action]->deactivate();
	//		}
	//		break;
	//	}
	//}

	//// If pressed button changed key bindings, update labels; otherwise consider other buttons in container
	//if (isKeyBinding)
	//	updateLabels();
	//else
	//	mGUIContainer.handleEvent(event);

	//return false;
}