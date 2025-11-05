#include "ViewHandler.h"
#include "World.hpp"
#include "Utility.hpp"
#include <iostream>

ViewHandler* ViewHandler::instance = new ViewHandler();

ViewHandler::ViewHandler() 
: mXViewScrollDistance(0)
, mYViewScrollDistance(0)
, mXViewAbsoluteTemp(0)
, mYViewAbsoluteTemp(0)
, mXScrollSpeed(0)
, mYScrollSpeed(0)
, mXMaxScroll(100)
, mYMaxScroll(100)
, mDefaultViewSize(1280, 960)
, mViewSize(mDefaultViewSize)
, mViewCenter()
, mLockViewScroll(false)
, mInViewArea(false)
, setAs(ViewHandler::offscreen)
{
	instance = this;
}

void ViewHandler::update(sf::View& view, sf::Window& window)
{
	float windowRatio = (float)window.getSize().x / (float)window.getSize().y;
	float viewRatio = view.getSize().x / (float)view.getSize().y;
	float sizeX = 1;
	float sizeY = 1;
	float posX = 0;
	float posY = 0;

	bool horizontalSpacing = false;
	if (setAs == letterboxing) {
		horizontalSpacing = true;
		if (windowRatio < viewRatio)
			horizontalSpacing = false;
	}
	if (setAs == offscreen || setAs == offscreenLensing) {
		horizontalSpacing = false;
		if (windowRatio < viewRatio)
			horizontalSpacing = true;
	}

	// If horizontalSpacing is true, the black bars will appear on the left and right side.
	// Otherwise, the black bars will appear on the top and bottom.

	if (horizontalSpacing) {
		sizeX = viewRatio / windowRatio;
		posX = (1 - sizeX) / 2.f;
	}

	else {
		sizeY = windowRatio / viewRatio;
		posY = (1 - sizeY) / 2.f;
	}

	mXViewAbsoluteTemp = view.getCenter().x;
	mYViewAbsoluteTemp = view.getCenter().y;

	view.setViewport(sf::FloatRect(posX, posY, sizeX, sizeY));
}

void ViewHandler::adaptView(sf::View& view, Player_Entity* player, sf::FloatRect bounds) 
{	
	sf::FloatRect Bounds = sf::FloatRect(view.getCenter() - view.getSize() / 2.f, view.getSize());
	sf::FloatRect worldBounds = bounds;

	if (mInViewArea == false) {
		mViewSize = mDefaultViewSize;
	}

	view.setSize(adjustToNumber(view.getSize().x, mViewSize.x / 50 + 0.00001, mViewSize.x), adjustToNumber(view.getSize().y, mViewSize.y / 50 + 0.00001, mViewSize.y));


	if (mLockViewScroll) {
		//view.setCenter(mViewCenter);
		view.setCenter(adjustToNumber(view.getCenter().x, mViewCenter.x / 50 + 0.00001, mViewCenter.x), adjustToNumber(view.getCenter().y, mViewCenter.y / 50 + 0.00001, mViewCenter.y));
	}

	mXViewScrollDistance = view.getSize().x / 2.f - 100;
	mYViewScrollDistance = view.getSize().y / 2.f - 200;

	mXScrollSpeed = 0;
	mYScrollSpeed = 0;

	if (!mLockViewScroll) {
		if (!(player->getPosition().x < worldBounds.left + mXViewScrollDistance)) {
			if (player->getPosition().x < Bounds.left + mXViewScrollDistance) {
				mXScrollSpeed = std::max(-mXMaxScroll, player->getPosition().x - (Bounds.left + mXViewScrollDistance));
			}
		}

		if (!(player->getPosition().x > worldBounds.left + worldBounds.width - mXViewScrollDistance)) {
			if (player->getPosition().x > Bounds.left + Bounds.width - mXViewScrollDistance) {
				mXScrollSpeed = std::min(mXMaxScroll, player->getPosition().x - (Bounds.left + Bounds.width - mXViewScrollDistance));
			}
		}

		if (player->getPosition().y < Bounds.top + mYViewScrollDistance) {
			mYScrollSpeed = std::max(-mYMaxScroll, player->getPosition().y - (Bounds.top + mYViewScrollDistance));
		}
		if (player->getPosition().y > Bounds.top + Bounds.height - mYViewScrollDistance) {
			mYScrollSpeed = std::min(mYMaxScroll, player->getPosition().y - (Bounds.top + Bounds.height - mYViewScrollDistance));
		}
	}

	view.move(mXScrollSpeed, mYScrollSpeed);
	mLockViewScroll = false;
	mInViewArea = false;
};

void ViewHandler::activeViewArea(ViewArea& area) {
	mViewSize = area.getViewSize();
	mInViewArea = true;
	if (area.getLockView()) {
		mLockViewScroll = true;
		mViewCenter = area.getViewCenter();
	}
}

float ViewHandler::getXViewAbsolute()
{
	return mXViewAbsoluteTemp;
}

float ViewHandler::getYViewAbsolute()
{
	return mYViewAbsoluteTemp;
}

float ViewHandler::getXViewScroll()
{
	return mXScrollSpeed;
};

float ViewHandler::getYViewScroll()
{
	return mYScrollSpeed;
}
ViewHandler* ViewHandler::getInstance()
{
	return instance;
}