#pragma once

#include <SFML/Graphics.hpp>

#include "ViewArea.h"

class ViewHandler
{
public:
	enum viewtype{
		offscreen,
		offscreenLensing,
		letterboxing
	};
	ViewHandler();
	void update(sf::View& view, sf::Window& window); //Mainly for letterboxing view
	void adaptView(sf::View& view, Player_Entity* player, sf::FloatRect bounds);
	void activeViewArea(ViewArea& area);

	float getXViewAbsolute();
	float getYViewAbsolute();

	float getXViewScroll();
	float getYViewScroll();

	static ViewHandler* getInstance();

private:
	float								mXViewScrollDistance; //Distance from side before view begins scrolling, 0 is no scroll
	float								mYViewScrollDistance;
	float								mXViewAbsoluteTemp;
	float								mYViewAbsoluteTemp;
	float								mXScrollSpeed;
	float								mYScrollSpeed;
	float								mXMaxScroll;
	float								mYMaxScroll;

	sf::Vector2f						mDefaultViewSize;
	sf::Vector2f						mViewSize;
	sf::Vector2f						mViewCenter;
	bool								mLockViewScroll;
	bool								mInViewArea;
	static ViewHandler*					instance;
	viewtype							setAs;
};

