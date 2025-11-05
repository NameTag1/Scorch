
#include "Container.hpp"

#include <SFML/Graphics.hpp>
#include <iostream>

namespace GUI
{

Container::Container()
: mChildren()
, mSelectedChild(-1)
{
}

void Container::pack(Component::Ptr component)
{
	mChildren.push_back(component);

	if (!hasSelection() && component->isSelectable())
		select(mChildren.size() - 1);
}

bool Container::isSelectable() const
{
    return false;
}

void Container::handleEvent(const sf::Event& event)
{
    // If we have selected a child then give it events
	if (hasSelection() && mChildren[mSelectedChild]->isActive())
	{
		mChildren[mSelectedChild]->handleEvent(event);
	}
	else if (event.type == sf::Event::KeyReleased)
	{
		if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up)
		{
			selectPrevious();
		}
		else if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down)
		{
			selectNext();
		}
		else if (event.key.code == sf::Keyboard::Return || event.key.code == sf::Keyboard::Space)
		{
			if (hasSelection())
				mChildren[mSelectedChild]->activate();
		}
	}
	if (event.type == sf::Event::MouseButtonReleased)
	{
		for (int i = 0; i < mChildren.size(); i++) {
			if (mChildren[mSelectedChild]->isSelectable() && getTransform().transformRect(mChildren[i]->getRect()).contains(event.mouseButton.x, event.mouseButton.y)) {
				select(i);
				mChildren[mSelectedChild]->activate();
				break;
			}
		}
	}
	if (event.type == sf::Event::MouseMoved)
	{
		for (int i = 0; i < mChildren.size(); i++) {
			if (getTransform().transformRect(mChildren[i]->getRect()).contains(event.mouseMove.x, event.mouseMove.y)) {
				select(i);
			}
		}
	}
}

void Container::updateRect(sf::FloatRect parrentRect)
{
	Component::updateRect(parrentRect);
	for (int i = 0; i < mChildren.size(); i++) {
		mChildren[i].get()->updateRect(getRect());
	}
}

void Container::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();

	for (const Component::Ptr& child : mChildren) {
		target.draw(*child, states);
	}
}

bool Container::hasSelection() const
{
	return mSelectedChild >= 0;
}

void Container::select(std::size_t index)
{
	if (mChildren[index]->isSelectable())
	{
		if (hasSelection())
			mChildren[mSelectedChild]->deselect();

		mChildren[index]->select();
		mSelectedChild = index;
	}
}

void Container::selectNext()
{
	if (!hasSelection())
		return;

	// Search next component that is selectable, wrap around if necessary
	int next = mSelectedChild;
	do
		next = (next + 1) % mChildren.size();
	while (!mChildren[next]->isSelectable());

	// Select that component
	select(next);
}

void Container::selectPrevious()
{
	if (!hasSelection())
		return;

	// Search previous component that is selectable, wrap around if necessary
	int prev = mSelectedChild;
	do
		prev = (prev + mChildren.size() - 1) % mChildren.size();
	while (!mChildren[prev]->isSelectable());

	// Select that component
	select(prev);
}

}
