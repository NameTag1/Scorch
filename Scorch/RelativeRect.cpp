#include "RelativeRect.h"

RelativeRect::RelativeRect(sf::FloatRect rect)
: x(rect.left)
, y(rect.top)
, w(rect.width)
, h(rect.height)
, mWH(Normal)
, mAnchor(TL)
{
	
}

RelativeRect::RelativeRect(sf::FloatRect rect, RelativeWH wh, Anchor a)
: x(rect.left)
, y(rect.top)
, w(rect.width)
, h(rect.height)
, mWH(wh)
, mAnchor(a)
{
}

void RelativeRect::update(sf::FloatRect parentRect)
{
	if (mWH == RelativeWH::Static) {
		tempRect.width = w;
		tempRect.height = h;
	}

	if (mWH == RelativeWH::WBased) {
		tempRect.width = parentRect.width * w;
		tempRect.height = tempRect.width / w * h;
	}

	if (mWH == RelativeWH::HBased) {
		tempRect.height = parentRect.height * h;
		tempRect.width = tempRect.height / h * w;
	}

	if (mWH == RelativeWH::WHBased) {
		if (parentRect.width * w > parentRect.height * h) {
			tempRect.width = parentRect.width * w;
			tempRect.height = tempRect.width / w * h;
		}
		else {
			tempRect.height = parentRect.height * h;
			tempRect.width = tempRect.height / h * w;
		}
	}

	if (mWH == RelativeWH::Normal) {
		tempRect.width = parentRect.width * w;
		tempRect.height = parentRect.height * h;
	}

	// Default position (use parent origin + relative offsets)
	tempRect.left = parentRect.left + parentRect.width * x;
	tempRect.top  = parentRect.top  + parentRect.height * y;


	if (mAnchor == Anchor::TL) {
		// already TL by default
	}

	if (mAnchor == Anchor::TR) {
		tempRect.left = parentRect.left + parentRect.width * x - tempRect.width;
		tempRect.top  = parentRect.top  + parentRect.height * y;
	}
	
	if (mAnchor == Anchor::BL) {
		tempRect.left = parentRect.left + parentRect.width * x;
		tempRect.top  = parentRect.top  + parentRect.height * y - tempRect.height;
	}

	if (mAnchor == Anchor::BR) {
		tempRect.left = parentRect.left + parentRect.width * x - tempRect.width;
		tempRect.top  = parentRect.top  + parentRect.height * y - tempRect.height;
	}

	if (mAnchor == Anchor::Center) {
		tempRect.left = parentRect.left + parentRect.width * x - tempRect.width/2;
		tempRect.top  = parentRect.top  + parentRect.height * y - tempRect.height/2;
	}

	//std::cout << tempRect.left << "\n";
}

void RelativeRect::setRect(sf::FloatRect newRect)
{
	x = newRect.left;
	y = newRect.top;
	w = newRect.width;
	h = newRect.height;
}

sf::FloatRect RelativeRect::getRect()
{
	return tempRect;
}

sf::FloatRect RelativeRect::getRect(sf::FloatRect target)
{
	update(target);
	return tempRect;
}

void RelativeRect::scaleSprite(sf::Sprite& sprite)
{
	// Use local bounds (unaffected by current transform/scale)
	sf::FloatRect local = sprite.getLocalBounds();
	if (local.width <= 0.f || local.height <= 0.f) return;

	float scalex = tempRect.getSize().x / local.width;
	float scaley = tempRect.getSize().y / local.height;

	// Set absolute scale instead of multiplying
	sprite.setScale(scalex, scaley);
}

void RelativeRect::scaleSprite(sf::Sprite& sprite, bool maintainRatio)
{
	// Use local bounds (unaffected by current transform/scale)
	sf::FloatRect local = sprite.getLocalBounds();
	if (local.width <= 0.f || local.height <= 0.f) return;

	float scalex = tempRect.getSize().x / local.width;
	float scaley = tempRect.getSize().y / local.height;

	if (mWH == RelativeWH::WBased) {
		scalex = tempRect.getSize().x / local.width;
		scaley = scalex;
	}

	if (mWH == RelativeWH::HBased) {
		scaley = tempRect.getSize().y / local.height;
		scalex = scaley;
	}

	if (mWH == RelativeWH::WHBased) {
		// Keep same behavior as before, but compute from local bounds
		if (tempRect.getSize().x * w > tempRect.getSize().y * h) {
			scalex = tempRect.getSize().x / local.width;
			scaley = scalex;
		}
		else {
			scaley = tempRect.getSize().y / local.height;
			scalex = scaley;
		}
	}

	// Set absolute scale instead of multiplying
	sprite.setScale(scalex, scaley);
}


