#pragma once

#ifndef Platform_h
#define Platfrom_h

#include "SceneNode.hpp"
#include "DataRetrivalTypes.h"
#include <SFML/Graphics.hpp>

#include "nlohmann/json.hpp"
using json = nlohmann::json;

class Platformer;

class Platform : public SceneNode
{
public:
	Platform(json data);
	virtual void adust_for_platformer(Platformer& platformer);
	virtual std::vector<unsigned int> getCategory() const;
	virtual unsigned int getPlatformType() const;
	virtual sf::FloatRect getBoundingRect() const;

	void setSFriction(float friction);
	float getSFriction();

	void setKFriction(float friction);
	float getKFriction();

private:
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	
private:
	float mSFriction;
	float mKFriction;
	DataRetrivalType::Platforms mType;
};

#endif 
