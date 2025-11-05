#include "ViewArea.h"
#include "DataTable.h"
#include <iostream>

ViewArea::ViewArea(DataRetrivalType::ViewAreas type)
: mArea(DATATABLE::viewData[type].area)
, mViewSize(DATATABLE::viewData[type].viewSize)
, mLockView(DATATABLE::viewData[type].lockView)
, mViewCenter(DATATABLE::viewData[type].viewCenter)
{
};

void ViewArea::setBounds(sf::IntRect newBounds) {
	mArea.width = newBounds.width;
	mArea.height = newBounds.height;
}

sf::FloatRect ViewArea::getBoundingRect() const {
	return getWorldTransform().transformRect(mArea);
};

std::vector<unsigned int> ViewArea::getCategory() const {
	std::vector<unsigned int> i;
	i.push_back(Category::ViewArea);
	return i;
};

sf::Vector2f ViewArea::getViewSize() {
	return mViewSize;
}

bool ViewArea::getLockView()
{
	return mLockView;
}

sf::Vector2f ViewArea::getViewCenter()
{
	return mViewCenter;
}

void ViewArea::updateCurrent(sf::Time dt, CommandQueue& commands) {
	
};

