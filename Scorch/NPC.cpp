#include "NPC.h"
#include "Logger.h"
#include "WorldCommand.h"
#include "World.hpp"

#include "SetWorldMode.h"

NPC::NPC(TextureHolder& textureHolder, json data)
	: Animatable(textureHolder, data["Animatable"])
	, mArrow(textureHolder, data["ArrowAnimation"])
	, mRunOnce(data["RunOnce"])
	, mDrawArrow(false)
	, mStickyInteract(false)
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
	mStickyInteract = true;
};

void NPC::updateCurrent(sf::Time dt, CommandQueue& commands) {
	Animatable::update(dt);
	mArrow.update(dt);
	mDrawArrow = false;
	if (mStickyInteract) {
		if (!mRunOnce) {
			mStickyInteract = false;
		}
		Logger::Instance->LogData(Logger::Action, "NPC Action!");
		std::vector<WorldAction*> actions;
		actions.push_back(new SetWorldMode(World::Story));
		World::getInstance()->pushAction(actions);
	}
};

void NPC::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
	//Logger::Instance->LogData(Logger::Action,"NPC DRAWING");
	target.draw(mAnimations, states);
	if (mDrawArrow == true) {
		target.draw(mArrow, states);
	}
};