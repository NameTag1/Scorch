#include "Platform.h"


Platform::Platform(json data)
: mSFriction(data["sFriction"])
, mKFriction(data["kFriction"])
{
}

void Platform::adust_for_platformer(Platformer& platformer){

};

std::vector<unsigned int> Platform::getCategory() const {
	std::vector<unsigned int> i;
	i.push_back(Category::Platform);
	return i;
}

unsigned int Platform::getPlatformType() const {
	return mType;
}

sf::FloatRect Platform::getBoundingRect() const {
	return sf::FloatRect();
};

void Platform::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
	
};

void Platform::setSFriction(float friction) {
	mSFriction = friction;
}

float Platform::getSFriction() {
	return mSFriction;
}

void Platform::setKFriction(float friction) {
	mKFriction = friction;
}

float Platform::getKFriction() {
	return mKFriction;
}
