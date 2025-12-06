#include "ViewArea.h"
#include "DataTable.h"

ViewArea::ViewArea(json data)
	: mArea(0,0,data["W"], data["H"])
	, mViewSize(data["ViewW"], data["ViewH"])
	, mLockView(data["ViewLock"])
	, mViewCenter(data["ViewX"],data["ViewY"])
{
};

void ViewArea::setBounds(sf::IntRect newBounds) {
	mArea.width = float(newBounds.width);
	mArea.height = float(newBounds.height);
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

