#pragma once

//#include "Player_Entity.h"
#include "SceneNode.hpp"
#include <vector>

class Player_Entity;

class Interactable : public SceneNode
{
public:
	virtual void interact(Player_Entity& player);
	virtual std::vector<unsigned int> getCategory() const;
};

