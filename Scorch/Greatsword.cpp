#include "Greatsword.h"
#include "Slash.h"
#include "MakeAttack.h"
#include "ChangeAnimation.h"
#include "With.h"
#include "Jump.h"

Greatsword::Greatsword(const TextureHolder& textures, Category::Type type)
	: mSprite(textures.get(Textures::Greatsword))
	, flipped(false)
	, Weapon(textures, type)
{
	mIcon = Textures::GreatswordIcon;

	mAttacks["Slot 1"] = new Slash(15, type, textures);

	mActions["Slot 1"] = new MakeAttack("Slot 1", Action::RunOnce);
	mActions["Slot 2"] = new With(new MakeAttack("Slot 1", Action::RunOnce), new Jump(), Action::RunOnce);
	mActions["Slot 3"] = new With(new MakeAttack("Slot 1", Action::RunOnce), new ChangeAnimation("greatsword"), Action::RunOnce);
}

void Greatsword::flip()
{
	if (left != flipped) {
		mSprite.scale(-1.f, 1.f);
		flipped = left;
	}
	/*if (up) {
		mSprite.scale(1.f, -1.f);
	}*/
}