#include "FallingPlatform.h"
#include "Logger.h"

FallingPlatform::FallingPlatform(TextureHolder& textureHolder, json data)
: mAnimation(textureHolder, data["Animation"])
, Platform(data["Platform"])
, mActivated(false)
, mResetDuration(sf::seconds(data["Duration"]))
, mResetTimer(mResetDuration)
{
	mAnimation.update(sf::seconds(0));
}


void FallingPlatform::adust_for_platformer(Platformer& platformer) {
	mActivated = true;
}

void FallingPlatform::updateCurrent(sf::Time dt, CommandQueue& Commands) {
	if (mActivated) {
		mResetTimer -= dt;
		if (!mAnimation.isFinished()) {
			mAnimation.update(dt);
		}
		if (mResetTimer <= sf::seconds(0)) {
			mResetTimer = mResetDuration;
			mAnimation.restart();
			mAnimation.update(sf::seconds(0));
			mActivated = false;
			Logger::Instance->LogData(Logger::Action, "Falling Reset");
		}
	}
};


std::vector<unsigned int> FallingPlatform::getCategory() const {
	std::vector<unsigned int> i;
	if (!mAnimation.isFinished()) {
		i.push_back(Category::Platform);
	}
	return i;
}

sf::FloatRect FallingPlatform::getBoundingRect() const {
	return getWorldTransform().transformRect(mAnimation.getGlobalBounds());
};

void FallingPlatform::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
	if (!mAnimation.isFinished()) {
		target.draw(mAnimation, states);
	}
};
