#include "Door.h"

Door::Door(TextureHolder& textureHolder, json data)
: mSprite(textureHolder.get(std::string(data["Texture"])))
, mArrow(textureHolder, data["ArrowAnim"])
, mDrawArrow(false)
, mScene(stringToScene(std::string(data["Scene"])))
, mPlayerPos({ data["PX"], data["PY"] })
{
	mArrow.move({(float(-1.0*(mSprite.getTexture()->getSize().x/2))), float(-1.0*(mArrow.getFrameSize().y)) });
}

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

void Door::touched(Player_Entity& player)
{
	mDrawArrow = true;
}

void Door::interact(Player_Entity& player) {
	
};

void Door::updateCurrent(sf::Time dt, CommandQueue& commands) {
	mArrow.update(dt);
	mDrawArrow = false;
};

void Door::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(mSprite, states);
	if (mDrawArrow == true) {
		target.draw(mArrow, states);
	}
};

