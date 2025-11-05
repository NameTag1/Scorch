#ifndef Normal_Platform_h
#define Normal_Platfrom_h

#include "Platform.h"
#include "DataTable.h"
#include "ResourceHolder.hpp"
#include <SFML/Graphics.hpp>

class Platformer;

class NormalPlatform : public Platform
{
public:
	NormalPlatform(TextureHolder& textureHolder, DataRetrivalType::Platforms type);
	NormalPlatform(TextureHolder& textureHolder, DataRetrivalType::Platforms type, sf::IntRect bounds);
	NormalPlatform(TextureHolder& textureHolder, NormalPlatformData data);
	void setBounds(sf::IntRect newBounds);
	virtual sf::FloatRect getBoundingRect() const;

private:
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	sf::Sprite mSprite;
};

#endif 