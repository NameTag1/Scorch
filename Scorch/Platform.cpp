#include "Platform.h"


Platform::Platform(json data)
: mFriction(data["Friction"])
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

void Platform::setFriction(int friction) {
	mFriction = friction;
}

int Platform::getFriction() {
	return mFriction;
}
