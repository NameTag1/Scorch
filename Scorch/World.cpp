#include "World.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

#include <algorithm>
#include <cmath>
#include <iostream>

#include "Utility.hpp"

#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.hpp"

#include "SceneNode.hpp"
#include "SpriteNode.hpp"
#include "Entity.hpp"

#include "CommandQueue.hpp"
#include "Command.hpp"

#include "Player_Entity.h"

#include "Door.h"

#include "AnimatedPlatform.h"
#include "FallingPlatform.h"
#include "NormalPlatform.h"
#include "Door.h"
#include "ViewArea.h"
#include "Enemy.h"

struct EntityMover
{
	EntityMover(float vx, float vy)
		: velocity(vx, vy)
	{
	}

	void operator() (Entity& entity, sf::Time) const
	{
		entity.accelerate(velocity);
	}

	sf::Vector2f velocity;
};

struct MovementCap
{
	MovementCap(float constantDeacell, float MaxX, float MaxY)
	: MaxVX(MaxX)
	, MaxVY(MaxY)
	, constantDeacell(constantDeacell)
	{
	}

	void operator() (Entity& entity, sf::Time) const
	{
		double changedVX = 0;
		double changedVY = 0;
		if (entity.getVelocity().x < 0) {
			changedVX = std::max((float)adjustToZero(entity.getVelocity().x, constantDeacell), -MaxVX);
		}
		if (entity.getVelocity().x > 0) {
			changedVX = std::min((float)adjustToZero(entity.getVelocity().x, constantDeacell), MaxVX);
		}

		if (entity.getVelocity().y < 0) {
			changedVY = std::max((float)entity.getVelocity().y, -MaxVY);
		}
		if (entity.getVelocity().y > 0) {
			changedVY = std::min((float)entity.getVelocity().y, MaxVY);
		}
		entity.setVelocity(changedVX, changedVY);
	}

	float MaxVX;
	float MaxVY;
	float constantDeacell;
};

World* World::instance = new World();

//1280, 960
//4/3 View Ratio

World::World()
: mWindow(*new sf::RenderWindow())
{
}

World::World(sf::RenderWindow& window)
: mWindow(window)
, mWorldView(window.getDefaultView())
, mTextures()
, mSceneGraph()
, mSceneLayers()
, mBuilder(nullptr)
, mPlayer(nullptr)
, mWorldBounds(-500.f, -500.f, mWorldView.getSize().x+2000, mWorldView.getSize().y+2000)
, mSpawnPosition(mWorldView.getSize().x / 2.f, mWorldBounds.height - mWorldView.getSize().y / 2.f)
, mGravity(60)
, mMaxFallVelocity(1200)
, mMaxXVelocity(800)
, mMaxYVelocity(2500)
, mConstantDeaccel(30)
, mScene(Scenes::Test)
{
	changeScene(Scenes::Test, sf::Vector2f(400, 400));
	instance = this;
}

void World::update(sf::Time dt)
{
	// Forward commands to scene graph, adapt velocity (scrolling, diagonal correction)
	while (!mCommandQueue.isWEmpty())
		onCommand(mCommandQueue.popWC());

	while (!mCommandQueue.isEmpty())
		mSceneGraph.onCommand(mCommandQueue.pop(), dt);

	enforceVelocityCap();
	adaptPlayerPosition();

	enforceGravity();

	mViewHandler.update(mWorldView, mWindow);
	mSceneGraph.update(dt, mCommandQueue);

	handleCollisions();

	adaptView();

	//if(mPlayer->getHitpoints()){}
	//mSceneGraph.removeWrecks();
}

void World::draw()
{
	mWindow.setView(mWorldView);

	mWindow.draw(mSceneGraph);
	std::vector<SceneNode*> i;
	mSceneGraph.findCategory(i, Category::Superlayer);
	for (auto n : i) {
		n->drawSolo(mWindow);
	}
}

CommandQueue& World::getCommandQueue()
{
	return mCommandQueue;
}

Player_Entity* World::getPlayer() {
	return nullptr;
}

double World::getGravity()
{
	return 1;
}

Scene_Change_Request World::requestSceneChange()
{
	return mSceneChangeRequest;
}

void World::prepareSceneForPlay(Scene_Builder* builder)
{
	mPlayer = builder->getPlayerEntity();
	mSceneLayers = builder->getLayers();
	mWorldView.setCenter(mPlayer->getPosition());
	mSceneChangeRequest = Scene_Change_Request();
	mSceneChangeRequest.scene = Scenes::Null;
}

World* World::getInstance()
{
	return instance;
}

void World::changeScene(Scenes scene, sf::Vector2f playerPos) {
	mSceneChangeRequest.scene = scene;
	mSceneChangeRequest.playerPos = playerPos;
};

void World::enforceGravity()
{
	Command Gravity;
	Gravity.action = derivedAction<Platformer>(EntityMover(0.f, mGravity));
	Gravity.category = Category::Platformer;
	mCommandQueue.push(Gravity);
}

void World::adaptPlayerPosition() {
	sf::Vector2f position = mPlayer->getPosition();
	
	position.x = std::max(position.x, mWorldBounds.left - 100);
	position.x = std::min(position.x, mWorldBounds.left + mWorldBounds.width + 100);
	position.y = std::max(position.y, mWorldBounds.top - 100);
	position.y = std::min(position.y, mWorldBounds.top + mWorldBounds.height + 100);

	mPlayer->setPosition(position);
};

void World::enforceVelocityCap() {
	Command VelocityCap;
	VelocityCap.action = derivedAction<Platformer>(MovementCap(mConstantDeaccel, mMaxXVelocity, mMaxYVelocity));
	VelocityCap.category = Category::Platformer;
	mCommandQueue.push(VelocityCap);
};

void World::adaptView() {
	mViewHandler.adaptView(mWorldView, mPlayer, mWorldBounds);
	mSceneLayers[MovingBackground]->setPosition(mViewHandler.getXViewAbsolute()*0.5, mViewHandler.getYViewAbsolute()*0.5); //Moves at 0.5 speed of view
	mSceneLayers[Forground]->setPosition(mViewHandler.getXViewAbsolute()*1.5, mViewHandler.getYViewAbsolute()*1.5); //Moves at 1.5 speed of view
};

sf::FloatRect World::getWorldViewBounds() {
	return sf::FloatRect(mWorldView.getCenter() - mWorldView.getSize() / 2.f, mWorldView.getSize());
}

sf::FloatRect World::getWorldBounds() {
	return mWorldBounds;
}

SceneNode* World::getSceneGraph()
{
	return &mSceneGraph;
}

void World::handleCollisions() {
	std::set<SceneNode::Pair> collisionPairs;
	mSceneGraph.checkSceneCollision(mSceneGraph, collisionPairs);

	for (SceneNode::Pair pair : collisionPairs) {
		if (matchesCategories(pair, Category::Platformer, Category::Platform)) {
			auto& platformer = static_cast<Platformer&>(*pair.first);
			auto& platform = static_cast<Platform&>(*pair.second);

			platformer.adust_for_platform(platform);
			platform.adust_for_platformer(platformer);
		}
		else if (matchesCategories(pair, Category::Player, Category::Door)) {
			auto& player = static_cast<Player_Entity&>(*pair.first);
			auto& door = static_cast<Door&>(*pair.second);
			
			if (player.getInteracting()) {
				door.interact(player);
				changeScene(door.getScene(), door.getPlayerPos());
				collisionPairs.clear(); //Otherwise you are referencing objects that have been destroyed by changeScene
				return;
			}
		}
		else if (matchesCategories(pair, Category::Player, Category::Interactable)) {
			auto& player = static_cast<Player_Entity&>(*pair.first);
			auto& thing = static_cast<Interactable&>(*pair.second);

			if (player.getInteracting()) {
				thing.interact(player);
				return;
			}
		}
		else if (matchesCategories(pair, Category::Player, Category::ViewArea)) {
			auto& viewArea = static_cast<ViewArea&>(*pair.second);

			mViewHandler.activeViewArea(viewArea);
		}
		else if (matchesCategories(pair, Category::Attack, Category::Entity)) {
			auto& attack = static_cast<Attack&>(*pair.first);
			Enemy& enemy = static_cast<Enemy&>(*pair.second);

			attack.dealDamage(&enemy);
		}
	}
}

void World::onCommand(const WorldCommand& command)
{
	command.action(*this);
}

std::array<SceneNode*, LayerCount>	World::getSceneLayers()
{
	return mSceneLayers;
}
