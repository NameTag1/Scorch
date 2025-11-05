#pragma once

#ifndef Platform_h
#define Platfrom_h

#include "SceneNode.hpp"
#include "DataRetrivalTypes.h"
#include <SFML/Graphics.hpp>


class Platformer;

class Platform : public SceneNode
{
public:
	Platform(int friction);
	Platform(int friction, DataRetrivalType::Platforms type);
	virtual void adust_for_platformer(Platformer& platformer);
	virtual std::vector<unsigned int> getCategory() const;
	virtual unsigned int getPlatformType() const;
	virtual sf::FloatRect getBoundingRect() const;
	void setFriction(int friction);
	int getFriction();

private:
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	
private:
	int mFriction;
	DataRetrivalType::Platforms mType;
};

#endif 
