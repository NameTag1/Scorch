#pragma once

#include "SceneNode.hpp"
#include "Animation.h"
#include "ChangeableAnimation.h"
#include <SFML/Graphics/RenderTarget.hpp>

class Animatable : public sf::Drawable
{
public:
	Animatable();
	Animatable(const TextureHolder& textures, json data);
	void setAnimation(std::string Animation);
	void setAnimation(std::string Animation, sf::Time mResetDuration);
	void setToDefault();

	void addAnimation(const std::string& name, Animation animation);
	void setDefaultAnimation(const std::string& name);

	sf::FloatRect 			getLocalBounds() const;
	sf::FloatRect 			getGlobalBounds() const;

	void 					update(sf::Time dt);

protected:
	ChangeableAnimation mAnimations;

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};


