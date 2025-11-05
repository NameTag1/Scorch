#include "Utility.hpp"
#include "SceneNode.hpp"
#include "Command.hpp"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>


SceneNode::SceneNode()
: mChildren()
, mParent(nullptr)
{
}

void SceneNode::attachChild(Ptr child)
{
	child->mParent = this;
	mChildren.push_back(std::move(child));
}

void SceneNode::clearChildren() {
	mChildren.erase(mChildren.begin(), mChildren.end());
};

SceneNode::Ptr SceneNode::detachChild(const SceneNode& node)
{
	auto found = std::find_if(mChildren.begin(), mChildren.end(), [&] (Ptr& p) { return p.get() == &node; });
	assert(found != mChildren.end());

	Ptr result = std::move(*found);
	result->mParent = nullptr;
	mChildren.erase(found);
	return result;
}

void SceneNode::update(sf::Time dt, CommandQueue& commands)
{
	updateCurrent(dt, commands);
	updateChildren(dt, commands);
}

void SceneNode::drawSolo(sf::RenderTarget& target)
{
	drawCurrent(target, getWorldTransform());
}

void SceneNode::updateCurrent(sf::Time dt, CommandQueue& commands)
{
	// Do nothing by default
}

void SceneNode::updateChildren(sf::Time dt, CommandQueue& commands)
{
	for(Ptr& child : mChildren)
		child->update(dt, commands);
}

void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// Apply transform of current node
	states.transform *= getTransform();

	// Draw node and children with changed transform
	drawCurrent(target, states);
	drawChildren(target, states);
}

void SceneNode::drawCurrent(sf::RenderTarget&, sf::RenderStates) const
{
	// Do nothing by default
}

void SceneNode::drawChildren(sf::RenderTarget& target, sf::RenderStates states) const
{
	for(const Ptr& child : mChildren)
		child->draw(target, states);
}

sf::Vector2f SceneNode::getWorldPosition() const
{
	return getWorldTransform() * sf::Vector2f();
}

sf::Transform SceneNode::getWorldTransform() const
{
	sf::Transform transform = sf::Transform::Identity;

	for (const SceneNode* node = this; node != nullptr; node = node->mParent)
		transform = node->getTransform() * transform;

	return transform;
}

void SceneNode::onCommand(const Command& command, sf::Time dt)
{
	// Command current node, if category matches
	if (matchesCategory(*this, static_cast<Category::Type>(command.category))) {
		command.action(*this, dt);
	}

	// Command children
	for(Ptr& child : mChildren)
		child->onCommand(command, dt);
}

std::vector<unsigned int> SceneNode::getCategory() const
{
	std::vector<unsigned int> i;
	i.push_back(Category::Scene);
	return i;
}

void SceneNode::checkSceneCollision(SceneNode& sceneGraph, std::set<Pair>& collisionPairs) {
	checkNodeCollision(sceneGraph, collisionPairs);

	for (Ptr& child : sceneGraph.mChildren) {
		checkSceneCollision(*child, collisionPairs);
	}
};

void SceneNode::checkNodeCollision(SceneNode& node, std::set<Pair>& collisionPairs) {
	if (this != &node && collision(*this, node) && !isDestroyed() && !node.isDestroyed()) {
		collisionPairs.insert(std::minmax(this, &node));
	}

	for (Ptr& child : mChildren) {
		child->checkNodeCollision(node, collisionPairs);
	}
}

void SceneNode::findCategory(std::vector<SceneNode*>& categoryMembers, Category::Type c)
{
	if (matchesCategory(*this, c)) {
		categoryMembers.push_back(this);
	}

	for (Ptr& child : mChildren) {
		child->findCategory(categoryMembers, c);
	}
};

sf::FloatRect SceneNode::getBoundingRect() const {
	return sf::FloatRect();
};

void SceneNode::removeWrecks() {
	auto wreckfieldBegin = std::remove_if(mChildren.begin(), mChildren.end(), std::mem_fn(&SceneNode::isMarkedForRemoval));
	mChildren.erase(wreckfieldBegin, mChildren.end());

	std::for_each(mChildren.begin(), mChildren.end(), std::mem_fn(&SceneNode::removeWrecks));
};

bool SceneNode::isMarkedForRemoval() const {
	return isDestroyed();
};

bool SceneNode::isDestroyed() const {
	return false;
};

bool SceneNode::collision(const SceneNode& lhs, const SceneNode& rhs) {
	return lhs.getBoundingRect().intersects(rhs.getBoundingRect());
}

float SceneNode::distance(const SceneNode& lhs, const SceneNode& rhs) {
	return length(lhs.getWorldPosition() - rhs.getWorldPosition());
}
