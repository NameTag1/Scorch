#pragma once

#include "DataRetrivalTypes.h"
#include "SceneNode.hpp"
#include "Animation.h"
#include <SFML/Graphics/RenderTarget.hpp>

class ChangeableAnimation : public sf::Drawable, public sf::Transformable
{
public:
	ChangeableAnimation();
	void setAnimation(unsigned int Animation, sf::Time Duration);
	void setToDefault();

	sf::FloatRect 			getLocalBounds() const;
	sf::FloatRect 			getGlobalBounds() const;

	void 					update(sf::Time dt);

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	std::vector<Animation> mAnimations;
	unsigned int mDefaultAnimation;
	unsigned int mCurrentAnimation;

};

