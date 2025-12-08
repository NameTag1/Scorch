#include "Scene_Builder.h"


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

#include "Logger.h"
#include <unordered_set>

// Recursively collect texture ids from a json value
namespace {
	using json = nlohmann::json;

	void collectTextures(const json& j, std::unordered_set<std::string>& out)
	{
		if (j.is_object())
		{
			for (auto it = j.begin(); it != j.end(); ++it)
			{
				const std::string key = it.key();
				const json& value = it.value();

				// match exact "Texture" or keys that contain "Texture" (e.g. "TextureArrow", "TextureFoo")
				if ((key == "Texture" || key.find("Texture") != std::string::npos) && value.is_string())
				{
					out.insert(value.get<std::string>());
				}

				// recurse into nested objects / arrays
				if (value.is_object() || value.is_array())
					collectTextures(value, out);
			}
		}
		else if (j.is_array())
		{
			for (const auto& el : j)
				collectTextures(el, out);
		}
	}
}

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
		Logger::Instance->LogData(Logger::Action, " -------- Loading Scene --------");

		clearLayers();

		DATATABLE::loadScene(scene);
		
		loadTextures(scene);

		for (auto& i : DATATABLE::SCENE_DATA[scene]) {
			std::string s = i["Type"];
			if (s == "Sprite_Node") {
				sf::Texture& backgroundTexture = mTextures->get(std::string(i["Texture"]));
				sf::IntRect backgroundTextureRect(0, 0, i["W"], i["H"]);
				if (i["Repeated"]) {
					backgroundTexture.setRepeated(true);
				}
				std::unique_ptr<SpriteNode> sprite(new SpriteNode(backgroundTexture, backgroundTextureRect));
				sprite->setPosition(i["X"], i["Y"]);
				if (i["Layer"] == "Moving_Background") {
					mSceneLayers[MovingBackground]->attachChild(std::move(sprite));
				}
				else if (i["Layer"] == "Background") {
					mSceneLayers[Background]->attachChild(std::move(sprite));
				}
				else if (i["Layer"] == "Forground") {
					mSceneLayers[Forground]->attachChild(std::move(sprite));
				}
			}
			else if (s == "Normal_Platform") {
				sf::IntRect platformRect(0, 0, i["W"], i["H"]);
				std::unique_ptr<NormalPlatform> platform(new NormalPlatform(*mTextures, i, platformRect));
				platform->setPosition(i["X"], i["Y"]);
				mSceneLayers[Play]->attachChild(std::move(platform));
			}
			else if (s == "Animated_Platform") {
				std::unique_ptr<AnimatedPlatform> platform(new AnimatedPlatform(*mTextures, i));
				platform->setPosition(i["X"], i["Y"]);
				mSceneLayers[Play]->attachChild(std::move(platform));
			}
			else if (s == "Falling_Platform") {
				std::unique_ptr<FallingPlatform> platform(new FallingPlatform(*mTextures, i));
				platform->setPosition(i["X"], i["Y"]);
				mSceneLayers[Play]->attachChild(std::move(platform));
			}
			else if (s == "Moving_Platform") {
				sf::IntRect movingPlatformRect(0, 0, i["W"], i["H"]);
				std::unique_ptr<MovingPlatform> movingPlatform(new MovingPlatform(*mTextures, i, movingPlatformRect));
				movingPlatform->setPosition(i["X"], i["Y"]);
				mSceneLayers[Play]->attachChild(std::move(movingPlatform));
			}
			else if (s == "Door") {
				std::unique_ptr<Door> door(new Door(*mTextures, i));
				door->setPosition(i["X"], i["Y"]);
				mSceneLayers[Play]->attachChild(std::move(door));
			}
			else if (s == "ViewArea") {
				std::unique_ptr<ViewArea> viewArea(new ViewArea(i));
				viewArea->setPosition(i["X"], i["Y"]);
				mSceneLayers[Play]->attachChild(std::move(viewArea));
			}
			else {
				Logger::Instance->LogData(Logger::Action, "Unknown Type " + s + " was Skipped!");
			}
			Logger::Instance->LogData(Logger::Action, "Created " + s);
		}

		if (scene == Scenes::Test) {												
			std::unique_ptr<Enemy> enemy(new Enemy(*mTextures));
			enemy->setPosition(1000, 600);
			mSceneLayers[Play]->attachChild(std::move(enemy));
		}

		std::unique_ptr<Player_Entity> player(new Player_Entity(*mTextures));
		mPlayer = Player_Entity::getInstance();
		player->setPosition(PlayerPos.x, PlayerPos.y);
		mSceneLayers[Play]->attachChild(std::move(player));

		Logger::Instance->LogData(Logger::Action, " -------- Scene Built --------");
	}
	catch (...) {
		Logger::Instance->LogData(Logger::Action, "Scenebuilder Exception");
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

void Scene_Builder::loadTextures(Scenes scene) {

	// collect all texture ids referenced by scene json (including nested objects)
	std::unordered_set<std::string> texturesToLoad;
	for (auto& element : DATATABLE::SCENE_DATA[scene]) {
		// element is assumed to be a nlohmann::json object
		collectTextures(element, texturesToLoad);
	}

	for (const auto& x : texturesToLoad) {
		auto it = DATATABLE::RESOURCE_LOCATIONS.find(x);
		if (it != DATATABLE::RESOURCE_LOCATIONS.end()) {
			mTextures->load(x, it->second);
			Logger::Instance->LogData(Logger::Action, "Scenebuilder loaded: " + x + " from " + it->second);
		}
		else {
			Logger::Instance->LogData(Logger::Action, "Texture id not found in RESOURCE_LOCATIONS: " + x);
		}
	}

	//mTextures->load(Textures::Background, "resources/Background.jpg");
	//mTextures->load(Textures::Background2, "resources/Background2.jpg");
	mTextures->load(Textures::Player, "resources/Player.png");
	mTextures->load("PlayerAni", "resources/PlayerAnimation.png");
	mTextures->load(Textures::Enemy, "resources/Enemy.png");
	mTextures->load(Textures::Platform, "resources/Platform.jpg");
	mTextures->get(Textures::Platform).setRepeated(true);
	mTextures->get("Platform").setRepeated(true);
	mTextures->load(Textures::TestAnimation, "resources/TestAnimated.bmp");
	mTextures->load(Textures::FallingSand, "resources/FallingSand.png");
	mTextures->load(Textures::Door, "resources/DefaultDoor.bmp");
	mTextures->load(Textures::DoorArrow, "resources/DoorArrow.png");
	mTextures->load(Textures::Slash, "resources/Slash.png");
	//mTextures->load(Textures::Greatsword, "resources/Greatsword.bmp");
	//mTextures->load(Textures::Default, "resources/Default.bmp");
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