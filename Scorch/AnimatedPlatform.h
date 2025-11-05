#ifndef Animated_Platform_h
#define Animated_Platfrom_h

#include "SceneNode.hpp"
#include "DataTable.h"
#include "Animation.h"
#include "ResourceHolder.hpp"
#include "Platform.h"

#include <SFML/Graphics.hpp>

class Platformer;

class AnimatedPlatform : public Platform
{
public:
	AnimatedPlatform(TextureHolder& textureHolder, DataRetrivalType::Platforms type);
	virtual void adust_for_platformer(Platformer& platformer);
	virtual sf::FloatRect getBoundingRect() const;

protected:
	virtual void updateCurrent(sf::Time dt, CommandQueue& Commands);

private:
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	Animation mAnimation;
};

#endif