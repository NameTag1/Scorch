
#include "Component.hpp"
#include <iostream>

namespace GUI
{

Component::Component()
: mIsSelected(false)
, mIsActive(false)
, mRect(sf::FloatRect())
{
}

Component::~Component()
{
}

bool Component::isSelected() const
{
	return mIsSelected;
}

void Component::select()
{
	mIsSelected = true;
}

void Component::deselect()
{
	mIsSelected = false;
}

bool Component::isActive() const
{
	return mIsActive;
}

void Component::activate()
{
	mIsActive = true;
}

void Component::deactivate()
{
	mIsActive = false;
}

void Component::setRelativeRect(RelativeRect r)
{
	mRect = r;
}

void Component::updateRect(sf::FloatRect parrentRect)
{
	mRect.update(parrentRect);
	setPosition(mRect.getRect().getPosition());
	//std::cout << mRect.getRect().left << "\n";
}

sf::FloatRect Component::getRect()
{
	return mRect.getRect();
}

}