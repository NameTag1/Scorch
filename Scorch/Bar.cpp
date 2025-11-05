#include "Bar.h"


namespace GUI
{

Bar::Bar()
: mCurrent(1)
, mMax(2)
{
	mMaxBar.setFillColor(sf::Color::Red);
	mCurrentBar.setFillColor(sf::Color::Green);
}

bool Bar::isSelectable() const
{
	return false;
}

void Bar::setMessure(float max, float current)
{
	mMax = max;
	mCurrent = current;
}

void Bar::handleEvent(const sf::Event&)
{
}

void Bar::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(mMaxBar, states);
	target.draw(mCurrentBar, states);
}


void Bar::updateRect(sf::FloatRect parrentRect)
{
	Component::updateRect(parrentRect);

	mMaxBar.setSize(mRect.getRect().getSize());
	mCurrentBar.setSize(sf::Vector2f(mRect.getRect().getSize().x/mMax*mCurrent, mRect.getRect().getSize().y));
}

}