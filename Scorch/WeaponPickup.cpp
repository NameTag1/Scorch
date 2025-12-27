#include "WeaponPickup.h"

#include "WeaponBuilder.h"

WeaponPickup::WeaponPickup(TextureHolder& textureHolder, json data)
	: mChild(createWeapon(textureHolder, data["Weapon"]))
	, mSprite(textureHolder.get(mChild->getIcon()))
	, mUsed(false)
{
}

void WeaponPickup::setBounds(sf::IntRect newBounds) {
	mSprite.setTextureRect(newBounds);
}

sf::FloatRect WeaponPickup::getBoundingRect() const {
	return getWorldTransform().transformRect(mSprite.getGlobalBounds());
};

std::vector<unsigned int> WeaponPickup::getCategory() const {
	std::vector<unsigned int> i(Interactable::getCategory());
	return i;
};

bool WeaponPickup::isMarkedForRemoval() const {
	return mUsed;
};

void WeaponPickup::interact(Player_Entity& player) {
	player.pushWeapon(mChild);
	mUsed = true;
};

void WeaponPickup::updateCurrent(sf::Time dt, CommandQueue& commands) {

};

void WeaponPickup::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(mSprite, states);
};