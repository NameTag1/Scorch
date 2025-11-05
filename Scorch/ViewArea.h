#pragma once

#include "SceneNode.hpp"
#include "Interactable.h"
#include "Animation.h"
#include "DataRetrivalTypes.h"
#include "DataTable.h"

class ViewArea : public SceneNode
{
public:
	ViewArea(DataRetrivalType::ViewAreas type);
	void setBounds(sf::IntRect newBounds);
	virtual sf::FloatRect getBoundingRect() const;
	virtual std::vector<unsigned int> getCategory() const;

	sf::Vector2f getViewSize();
	bool getLockView();
	sf::Vector2f getViewCenter();

private:
	virtual void updateCurrent(sf::Time dt, CommandQueue& commands);

private:
	sf::FloatRect mArea;
	sf::Vector2f mViewSize;
	bool mLockView;
	sf::Vector2f mViewCenter;
};
