#ifndef Falling_Platform_h
#define Falling_Platfrom_h

#include "SceneNode.hpp"
#include "Platform.h"
#include "DataTable.h"
#include "Animation.h"
#include "ResourceHolder.hpp"

#include <SFML/Graphics.hpp>

class Platformer;

class FallingPlatform : public Platform
{
public:
	FallingPlatform(TextureHolder& textureHolder, DataRetrivalType::Platforms type);
	virtual void adust_for_platformer(Platformer& platformer);
	virtual std::vector<unsigned int> getCategory() const;
	virtual sf::FloatRect getBoundingRect() const;

protected:
	virtual void updateCurrent(sf::Time dt, CommandQueue& Commands);

private:
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	sf::Time mReset;
	bool mActivated;
	Animation mAnimation;
};

#endif