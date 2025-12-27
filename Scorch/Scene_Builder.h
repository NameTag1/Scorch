#pragma once

#include <array>
#include "SceneNode.hpp"
#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.hpp"
#include "Scenes.h"

#include "Player_Entity.h"


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
	Scene_Builder(SceneNode& sceneGraph, TextureHolder* textures, FontHolder* founts);
	~Scene_Builder();
	void buildScene(Scenes scene, sf::Vector2f PlayerPos);

	Player_Entity* getPlayerEntity();
	std::array<SceneNode*, LayerCount> getLayers();
	void clearLayers();

	static Scene_Builder* getInstance();

private:
	void loadTextures(Scenes scene);
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

