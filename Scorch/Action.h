#pragma once

#include "CommandQueue.hpp"
#include "SceneNode.hpp"

class Action
{
public:
	enum Type {
		Live, //ALL Live Actions Run then Deleted each clock cycle
		RunOnce, //Runs normally then deleted
		Persistent //Runs and never deleted
	};

public:
	Action(Type a);
	virtual void update(sf::Time dt, CommandQueue& Commands, SceneNode& target);
	virtual bool isFinnished();
	virtual void reset();
	
	Type mType;
};
