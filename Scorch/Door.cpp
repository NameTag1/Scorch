#include "Door.h"

Door::Door(TextureHolder& textureHolder, DataRetrivalType::Doors type, Scenes scene)
: mSprite(textureHolder.get(DATATABLE::doorData[type].texture))
, mScene(scene)
, mPlayerPos(DATATABLE::doorData[type].playerPos)
, mArrow(textureHolder.get(DATATABLE::doorData[type].texture))
{
};

void Door::setBounds(sf::IntRect newBounds) {
	mSprite.setTextureRect(newBounds);
}

sf::FloatRect Door::getBoundingRect() const {
	return getWorldTransform().transformRect(mSprite.getGlobalBounds());
};

std::vector<unsigned int> Door::getCategory() const {
	std::vector<unsigned int> i(Interactable::getCategory());
	i.push_back(Category::Door);
	return i;
};

Scenes Door::getScene() const {
	return mScene;
};

sf::Vector2f Door::getPlayerPos() const {
	return mPlayerPos;
}

void Door::interact(Player_Entity& player) {
	
};

void Door::updateCurrent(sf::Time dt, CommandQueue& commands) {

};

void Door::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(mSprite, states);
};

