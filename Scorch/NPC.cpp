#include "NPC.h"
#include "Logger.h"

NPC::NPC(TextureHolder& textureHolder, json data)
	: Animatable(textureHolder, data["Animatable"])
	, mArrow(textureHolder, data["ArrowAnimation"])
	, mDrawArrow(false)
{
	mArrow.move({ (float(-1.0 * (Animatable::getLocalBounds().getSize().x / 2))), float(-1.0 * (mArrow.getFrameSize().y + 50))});
}

sf::FloatRect NPC::getBoundingRect() const {
	return getWorldTransform().transformRect(Animatable::getGlobalBounds());
};

std::vector<unsigned int> NPC::getCategory() const {
	std::vector<unsigned int> i(Interactable::getCategory());
	i.push_back(Category::NPC);
	return i;
};

void NPC::touched(Player_Entity& player)
{
	mDrawArrow = true;
}

void NPC::interact(Player_Entity& player) {

};

void NPC::updateCurrent(sf::Time dt, CommandQueue& commands) {
	Animatable::update(dt);
	mArrow.update(dt);
	mDrawArrow = false;
};

void NPC::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
	//Logger::Instance->LogData(Logger::Action,"NPC DRAWING");
	target.draw(mAnimations, states);
	if (mDrawArrow == true) {
		target.draw(mArrow, states);
	}
};