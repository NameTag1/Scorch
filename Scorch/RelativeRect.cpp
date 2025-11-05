#include "RelativeRect.h"
#include <iostream>

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

	tempRect.left = 0;//(parentRect.width) - (tempRect.width / 2);
	tempRect.top = 0; //(parentRect.height) - (tempRect.height / 2);


	if (mAnchor == Anchor::TL) {
		tempRect.left = parentRect.width * x;
		tempRect.top = parentRect.height * y;
	}

	if (mAnchor == Anchor::TR) {
		tempRect.left = parentRect.width * x - tempRect.width;
		tempRect.top = parentRect.height * y;
	}
	
	if (mAnchor == Anchor::BL) {
		tempRect.left = parentRect.width * x;
		tempRect.top = parentRect.height * y - tempRect.height;
	}

	if (mAnchor == Anchor::BR) {
		tempRect.left = parentRect.width * x - tempRect.width;
		tempRect.top = parentRect.height * y - tempRect.height;
	}

	if (mAnchor == Anchor::Center) {
		tempRect.left = parentRect.width * x - tempRect.width/2;
		tempRect.top = parentRect.height * y - tempRect.height/2;
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
	float scalex = tempRect.getSize().x / sprite.getGlobalBounds().width;
	float scaley = tempRect.getSize().y / sprite.getGlobalBounds().height;

	sprite.scale(scalex, scaley);
}

void RelativeRect::scaleSprite(sf::Sprite& sprite, bool maintainRatio)
{
	float scalex = tempRect.getSize().x / sprite.getGlobalBounds().width;
	float scaley = tempRect.getSize().y / sprite.getGlobalBounds().height;

	if (mWH == RelativeWH::WBased) {
		scalex = tempRect.getSize().x / sprite.getGlobalBounds().width;
		scaley = scalex;
	}

	if (mWH == RelativeWH::HBased) {
		scaley = tempRect.getSize().y / sprite.getGlobalBounds().height;
		scalex = scaley;
	}

	if (mWH == RelativeWH::WHBased) {
		if (tempRect.getSize().x * w > tempRect.getSize().y * h) {
			scalex = tempRect.getSize().x / sprite.getGlobalBounds().width;
			scaley = scalex;
		}
		else {
			scaley = tempRect.getSize().y / sprite.getGlobalBounds().height;
			scalex = scaley;
		}
	}

	sprite.scale(scalex, scaley);
}


