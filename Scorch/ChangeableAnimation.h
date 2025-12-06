#pragma once

#include "DataRetrivalTypes.h"
#include "SceneNode.hpp"
#include "Animation.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <map>

class ChangeableAnimation : public sf::Drawable, public sf::Transformable
{
public:
	ChangeableAnimation();
	void changeAnimation(std::string animation, sf::Time mResetDuration);
	void pushAnimation(std::string animation, TextureHolder& textureHolder, json animationData);
	void setToDefault();

	sf::FloatRect 			getLocalBounds() const;
	sf::FloatRect 			getGlobalBounds() const;

	void 					update(sf::Time dt);

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	std::map<std::string, Animation> mAnimations;
	std::string mDefaultAnimation;
	std::string mCurrentAnimation;

};

