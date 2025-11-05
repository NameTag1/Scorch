#include "Scene_Builder.h"

#include <iostream>

#include "NormalPlatform.h"
#include "FallingPlatform.h"
#include "AnimatedPlatform.h"
#include "Door.h"
#include "Player_Entity.h"
#include "SpriteNode.hpp"
#include "ViewArea.h"
#include "MovingPlatform.h"
#include "Enemy.h"
#include "Greatsword.h"

Scene_Builder* Scene_Builder::instance = new Scene_Builder();

Scene_Builder::Scene_Builder()
{
}

Scene_Builder::Scene_Builder(SceneNode& sceneGraph, TextureHolder* Textures, FontHolder* Fonts)
: mSceneGraph(&sceneGraph)
, mTextures(Textures)
, mFonts(Fonts)
, buildPlayer(false)
{
	instance = this;
	addLayers();
};

void Scene_Builder::buildScene(Scenes scene, sf::Vector2f PlayerPos) {
	try {

		clearLayers();
		loadTextures();

		if (scene == Scenes::Test) {
			sf::Texture& backgroundTexture = mTextures->get(Textures::Background);
			sf::IntRect backgroundTextureRect(0, 0, 50000, 50000);
			backgroundTexture.setRepeated(true);
			std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(backgroundTexture, backgroundTextureRect));
			backgroundSprite->setPosition(-25000, -25000);
			mSceneLayers[Background]->attachChild(std::move(backgroundSprite));
			
			sf::Texture& moveBackgroundTexture = mTextures->get(Textures::Platform);
			sf::IntRect moveBackgroundTextureRect(0, 0, 100, 100);
			moveBackgroundTexture.setRepeated(true);
			std::unique_ptr<SpriteNode> movingBackgroundSprite(new SpriteNode(moveBackgroundTexture, moveBackgroundTextureRect));
			movingBackgroundSprite->setPosition(200, 400);
			mSceneLayers[MovingBackground]->attachChild(std::move(movingBackgroundSprite));
			
			sf::Texture& forgroundTexture = mTextures->get(Textures::Platform);
			sf::IntRect forgroundTextureRect(0, 0, 100, 100);
			forgroundTexture.setRepeated(true);
			std::unique_ptr<SpriteNode> forgroundSprite(new SpriteNode(forgroundTexture, forgroundTextureRect));
			forgroundSprite->setPosition(200, 400);
			mSceneLayers[Forground]->attachChild(std::move(forgroundSprite));
			
			sf::IntRect platformARect(0, 0, 3000, 200);
			std::unique_ptr<NormalPlatform> platformA(new NormalPlatform(*mTextures, DataRetrivalType::Platform, platformARect));
			platformA->setPosition(-1200, 800);
			mSceneLayers[Play]->attachChild(std::move(platformA));
			
			sf::IntRect platformBRect(0, 0, 200, 150);
			std::unique_ptr<NormalPlatform> platformB(new NormalPlatform(*mTextures, DataRetrivalType::Platform, platformBRect));
			platformB->setPosition(200, 600);
			mSceneLayers[Play]->attachChild(std::move(platformB));
			
			sf::IntRect platformCRect(0, 0, 200, 50);
			std::unique_ptr<NormalPlatform> platformC(new NormalPlatform(*mTextures, DataRetrivalType::Platform, platformCRect));
			platformC->setPosition(800, 400);
			mSceneLayers[Play]->attachChild(std::move(platformC));
			
			std::unique_ptr<AnimatedPlatform> animatedPlatform(new AnimatedPlatform(*mTextures, DataRetrivalType::Animated));
			animatedPlatform->setPosition(400, 200);
			mSceneLayers[Play]->attachChild(std::move(animatedPlatform));
			
			std::unique_ptr<FallingPlatform> fallingPlatform(new FallingPlatform(*mTextures, DataRetrivalType::SandAnimatedFalling));
			fallingPlatform->setPosition(100, 300);
			mSceneLayers[Play]->attachChild(std::move(fallingPlatform));
			
			std::unique_ptr<Door> door(new Door(*mTextures, DataRetrivalType::DoorToHome, Scenes::Test2));
			door->setPosition(800, 650);
			mSceneLayers[Play]->attachChild(std::move(door));

			std::unique_ptr<Enemy> enemy(new Enemy(*mTextures));
			enemy->setPosition(1000, 600);
			mSceneLayers[Play]->attachChild(std::move(enemy));
		}
		else if (scene == Scenes::Test2) {
			sf::Texture& backgroundTexture = mTextures->get(Textures::Background2);
			sf::IntRect backgroundTextureRect(0, 0, 2560, 1440);
			backgroundTexture.setRepeated(false);
			std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(backgroundTexture, backgroundTextureRect));
			backgroundSprite->setPosition(0, 0);
			mSceneLayers[Background]->attachChild(std::move(backgroundSprite)); 
			
			sf::IntRect platformARect(0, 0, 1500, 20);
			std::unique_ptr<NormalPlatform> platformA(new NormalPlatform(*mTextures, DataRetrivalType::Platform, platformARect));
			platformA->setPosition(0, 800);
			mSceneLayers[Play]->attachChild(std::move(platformA));

			std::unique_ptr<Door> door(new Door(*mTextures, DataRetrivalType::DoorOutHome, Scenes::Test));
			door->setPosition(800, 650);
			mSceneLayers[Play]->attachChild(std::move(door));

			std::unique_ptr<ViewArea> viewAreaA(new ViewArea(DataRetrivalType::TestViewArea));
			viewAreaA->setPosition(200, 450);
			mSceneLayers[Play]->attachChild(std::move(viewAreaA));

			std::unique_ptr<ViewArea> viewAreaB(new ViewArea(DataRetrivalType::Test2ViewArea));
			viewAreaB->setPosition(1200, 450);
			mSceneLayers[Play]->attachChild(std::move(viewAreaB));

			sf::IntRect movingPlatformRect(0, 0, 200, 50);
			std::unique_ptr<MovingPlatform> movingPlatform(new MovingPlatform(*mTextures, DataRetrivalType::Moving, movingPlatformRect));
			movingPlatform->setPosition(800, 400);
			mSceneLayers[Play]->attachChild(std::move(movingPlatform));

			/*sf::IntRect movingPlatformRect2(0, 0, 200, 50);
			std::unique_ptr<MovingPlatform> movingPlatform2(new MovingPlatform(*mTextures, DataRetrivalType::Moving2, movingPlatformRect2));
			movingPlatform2->setPosition(800, 200);
			mSceneLayers[Play]->attachChild(std::move(movingPlatform2));*/
		}

		std::unique_ptr<Player_Entity> player(new Player_Entity(*mTextures));
		mPlayer = Player_Entity::getInstance();
		player->setPosition(PlayerPos.x, PlayerPos.y);
		mSceneLayers[Play]->attachChild(std::move(player));
	}
	catch (...) {
		std::cout << "Failed to Load Scene";
	}
};

Player_Entity* Scene_Builder::getPlayerEntity() {
	return mPlayer;
};

std::array<SceneNode*, LayerCount> Scene_Builder::getLayers() {
	return mSceneLayers;
}

Scene_Builder* Scene_Builder::getInstance()
{
	return instance;
}

void Scene_Builder::loadTextures() {
	mTextures->load(Textures::Background, "resources/Background.jpg");
	mTextures->load(Textures::Background2, "resources/Background2.jpg");
	mTextures->load(Textures::Player, "resources/Player.png");
	mTextures->load(Textures::Enemy, "resources/Enemy.png");
	mTextures->load(Textures::Platform, "resources/Platform.jpg");
	mTextures->get(Textures::Platform).setRepeated(true);
	mTextures->load(Textures::TestAnimation, "resources/TestAnimated.bmp");
	mTextures->load(Textures::FallingSand, "resources/FallingSand.png");
	mTextures->load(Textures::Door, "resources/DefaultDoor.bmp");
	mTextures->load(Textures::DoorArrow, "resources/DoorArrow.png");
	mTextures->load(Textures::Slash, "resources/Slash.png");
	mTextures->load(Textures::Greatsword, "resources/Greatsword.bmp");
	mTextures->load(Textures::Default, "resources/Default.bmp");
};

void Scene_Builder::clearLayers() {
	for (std::size_t i = 0; i < LayerCount; ++i)
	{
		mSceneLayers[i]->clearChildren();
	}
};

void Scene_Builder::addLayers() {
	for (std::size_t i = 0; i < LayerCount; ++i)
	{
		SceneNode::Ptr layer(new SceneNode());
		mSceneLayers[i] = layer.get();

		mSceneGraph->attachChild(std::move(layer));
	}
};