#include "Greatsword.h"
#include "Slash.h"
#include "MakeAttack.h"
#include "With.h"
#include "Jump.h"
#include <iostream>

Greatsword::Greatsword(const TextureHolder& textures, Category::Type type)
	: mSprite(textures.get(Textures::Greatsword))
	, flipped(false)
	, Weapon(textures, type)
{
	mIcon = Textures::Greatsword;

	mAttacks["Slot 1"] = new Slash(15, type, textures);

	mActions["Slot 1"] = new MakeAttack("Slot 1", Action::RunOnce);
	mActions["Slot 2"] = new With(new MakeAttack("Slot 1", Action::RunOnce), new Jump(), Action::RunOnce);
}

void Greatsword::flip()
{
	if (left != flipped) {
		mSprite.scale({ -1.f, 1.f });
		flipped = left;
	}
	/*if (up) {
		mSprite.scale(1.f, -1.f);
	}*/
}

void Greatsword::updateCurrent(sf::Time dt, CommandQueue& commands) 
{

}

void Greatsword::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const 
{
	target.draw(mSprite, states);
}