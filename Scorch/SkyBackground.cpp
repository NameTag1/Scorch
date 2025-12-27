#include "SkyBackground.h"

#include "TimeKeeper.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include "Utility.hpp"

SkyBackground::SkyBackground(TextureHolder& textures)
	: mBackground({10000000,10000000}) //Realistically Infinite
{
	mBackground.setPosition(-mBackground.getSize().x / 2, -mBackground.getSize().y / 2);
}

void SkyBackground::updateCurrent(sf::Time dt, CommandQueue& commands)
{
	std::vector<Timekeeper::Period> p = Timekeeper::getTimeperiod();
	if (contains(p, Timekeeper::Dawn) || contains(p, Timekeeper::Dusk)) {
		mBackground.setFillColor(sf::Color(255, 153, 51)); //Orange
	}
	else if (contains(p, Timekeeper::Day) || contains(p, Timekeeper::Noon)) {
		mBackground.setFillColor(sf::Color(135, 206, 235)); //Sky Blue
	}
	else {
		mBackground.setFillColor(sf::Color(25, 25, 112)); //Midnight Blue
	}
}

void SkyBackground::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mBackground, states);
}
