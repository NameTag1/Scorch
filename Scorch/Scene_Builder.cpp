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
#include "WeaponPickup.h"

#include "Logger.h"
#include <unordered_set>
#include "NPC.h"
#include "SkyBackground.h"

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

Scene_Builder* Scene_Builder::instance = nullptr;

Scene_Builder::Scene_Builder(SceneNode& sceneGraph, TextureHolder* Textures, FontHolder* Fonts)
: mSceneGraph(&sceneGraph)
, mTextures(Textures)
, mFonts(Fonts)
, buildPlayer(false)
, mPlayer(nullptr)
{
	DATATABLE::loadEntityData();
	instance = this;
	addLayers();
}

Scene_Builder::~Scene_Builder()
{
	Player_Entity::resetInstance();
}

void Scene_Builder::buildScene(Scenes scene, sf::Vector2f PlayerPos) {
	try {
		Logger::Instance->LogData(Logger::Action, "-------- Loading Scene --------");

		// If a player exists, detach it from the Play layer to preserve it across the clear.
		SceneNode::Ptr savedPlayer;
		Player_Entity* existing = Player_Entity::getInstance();
		if (existing != nullptr && mSceneLayers[Play] != nullptr) {
			// detachChild returns ownership (unique_ptr) if the child is found
			savedPlayer = mSceneLayers[Play]->detachChild(*existing);
			// if savedPlayer is non-null we now own the player node in savedPlayer
			// When exiting then re-entering the game, player exists but is not attached to Play layer, thus returns nullptr
		}

		clearLayers();

		DATATABLE::loadScene(scene);
		DATATABLE::loadEntityData();
		
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
			else if (s == "View_Area") {
				std::unique_ptr<ViewArea> viewArea(new ViewArea(i));
				viewArea->setPosition(i["X"], i["Y"]);
				mSceneLayers[Play]->attachChild(std::move(viewArea));
			}
			else if (s == "Weapon_Pickup") {
				std::unique_ptr<WeaponPickup> pickup(new WeaponPickup(*mTextures, i));
				pickup->setPosition(i["X"], i["Y"]);
				mSceneLayers[Play]->attachChild(std::move(pickup));
			}
			else if (s == "NPC") {
				std::unique_ptr<NPC> npc(new NPC(*mTextures, i));
				npc->setPosition(i["X"], i["Y"]);
				mSceneLayers[Play]->attachChild(std::move(npc));
			}
			else {
				Logger::Instance->LogData(Logger::Action, "Unknown Type " + s + " was Skipped!");
			}
			Logger::Instance->LogData(Logger::Action, "Created " + s);
		}

		if (scene == Scenes::Test) {
			std::unique_ptr<SkyBackground> sky(new SkyBackground(*mTextures));
			mSceneLayers[Background]->attachChild(std::move(sky));
			Logger::Instance->LogData(Logger::Action, "Sky Backgournd Created");

			std::unique_ptr<Enemy> enemy(new Enemy(*mTextures));
			enemy->setPosition(1000, 600);
			mSceneLayers[Play]->attachChild(std::move(enemy));
		}

		if (scene == Scenes::Test2) {
		}

		// Reattach or create the player:
		if (Player_Entity::getInstance() == nullptr) {
			// No player exists yet: create one and attach it to Play
			SceneNode::Ptr newPlayer(new Player_Entity(*mTextures, DATATABLE::ENTITY_DATA["Player"]));
			// instance is set inside Player_Entity ctor
			newPlayer->setPosition(PlayerPos.x, PlayerPos.y);
			mSceneLayers[Play]->attachChild(std::move(newPlayer));
			Logger::Instance->LogData(Logger::Action, "Player instance created.");
		}
		else {
			// Player exists already.
			if (savedPlayer) {
				// We detached it earlier; reattach to Play layer
				savedPlayer->setPosition(PlayerPos.x, PlayerPos.y);
				mSceneLayers[Play]->attachChild(std::move(savedPlayer));
				Logger::Instance->LogData(Logger::Action, "Player taken out of scene and saved.");
			}
			else {
				// Could not find player node in layers (maybe already held elsewhere). Just update mPlayer pointer and position.
				Player_Entity* p = Player_Entity::getInstance();
				if (p) {
					p->setPosition(PlayerPos.x, PlayerPos.y);
					// Log so we can inspect unexpected states
					Logger::Instance->LogData(Logger::Action, "Player instance exists but was not attached; position updated only.");
				}
			}
		}
	
		// Update stored mPlayer pointer
		mPlayer = Player_Entity::getInstance();
		mPlayer->setInteracting(false);

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
	for (auto& element : DATATABLE::ENTITY_DATA) {
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

	mTextures->load(Textures::Enemy, "resources/Enemy.png");
	mTextures->get("Platform").setRepeated(true);
	mTextures->load(Textures::Slash, "resources/Slash.png");
	mTextures->load(Textures::GreatswordIcon, "resources/GreatswordIcon.png");
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