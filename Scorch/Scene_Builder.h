#pragma once

#include <array>
#include "SceneNode.hpp"
#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.hpp"

#include "Player_Entity.h"

enum Scenes {
	Null,
	Test,
	Test2,
	Sietch,
	Home,
	Dunes,
	MagmaFields,
	Canyons
};

enum Layer
{
	Background,
	MovingBackground,
	Play,
	AttackLayer,
	Forground,
	LayerCount
};

class Scene_Builder
{
public:
	Scene_Builder();
	Scene_Builder(SceneNode& sceneGraph, TextureHolder* textures, FontHolder* founts);
	void buildScene(Scenes scene, sf::Vector2f PlayerPos);

	Player_Entity* getPlayerEntity();
	std::array<SceneNode*, LayerCount> getLayers();
	void clearLayers();

	static Scene_Builder* getInstance();

private:
	void loadTextures();
	void addLayers();

private:
	bool buildPlayer;

	SceneNode* mSceneGraph;
	std::array<SceneNode*, LayerCount> mSceneLayers;
	Player_Entity* mPlayer;

	TextureHolder* mTextures;
	FontHolder* mFonts;

	static Scene_Builder* instance;
};

