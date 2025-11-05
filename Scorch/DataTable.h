#pragma once

#ifndef DataTable_hpp
#define DataTable_hpp

#include "ResourceIdentifiers.hpp"
#include "Scene_Builder.h"
#include "DataRetrivalTypes.h"

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>

#include <vector>
#include <functional>

//#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/filereadstream.h"
#include "rapidjson/istreamwrapper.h"

using namespace rapidjson;

namespace DataStorageTypes{
	enum Datatype {
		Entity,
		Animation,
		Platform,
		AnimatedPlatform,
		FallingPlatform,
	};
}

struct SceneElement
{
	unsigned int Layer;
	unsigned int Scene;
	sf::Vector2f Position;
	unsigned int DataType;
	unsigned int DataRetrivalPosition; //DataRetrivalType
};

struct EntityData
{
	int								hitpoints;
	float							speed;
	Textures::ID					texture;
	sf::IntRect						textureRect;
};

struct AnimationData
{
	sf::Vector2i 					mFrameSize;
	std::size_t 					mNumFrames;
	sf::Time 						mDuration;
	bool 							mRepeat;
};

struct PlatformData
{
	int								friction;
	Textures::ID					texture;
};

struct NormalPlatformData
{
	PlatformData					platform;
	sf::IntRect						rect;
};

struct AnimatedPlatformData
{
	PlatformData					platform;
	AnimationData					animation;
};

struct FallingPlatformData
{
	PlatformData					platform;
	sf::Time						resetTime;
	AnimationData					animation;
};

struct MovingPlatformData
{
	PlatformData					platform;
	sf::Vector2i					startingPoint;
	sf::Vector2i					endPoint;
	sf::Vector2f					speed;
	float							cushion;
};

struct DoorData
{
	Textures::ID					texture;
	Textures::ID					arrowTexture;
	sf::Vector2f					playerPos;
};

struct ViewAreaData
{
	sf::FloatRect					area;
	sf::Vector2f					viewSize;
	bool							lockView;
	sf::Vector2f					viewCenter;
};

//Updated minimally after Initialization. 
//Look to settings for Application-updated consts (which ig means their not consts...)
class DATATABLE {
public:
	static void prepareData();
	static void prepareJsonFile();
	
	static std::vector<EntityData> entityData;
	static std::vector<PlatformData> platformData;
	static std::vector<AnimationData> animationData;
	static std::vector<AnimatedPlatformData>	animatedPlatformData;
	static std::vector<FallingPlatformData>	fallingPlatformData;
	static std::vector<MovingPlatformData>	movingPlatformData;
	static std::vector<DoorData>	doorData;
	static std::vector<ViewAreaData> viewData;
	static std::map<Scenes, std::vector<SceneElement*>> SceneData;

private:
	//static Document JSONDATA;
	static const std::string JSON_FILEPATH;
	static std::vector<EntityData>	initializeEntityData();
	static std::vector<PlatformData> initializePlatformData();
	static std::vector<AnimationData> initializeAnimationData();
	static std::vector<AnimatedPlatformData> initializeAnimatedPlatformData();
	static std::vector<FallingPlatformData> initializeFallingPlatformData();
	static std::vector<MovingPlatformData> initializeMovingPlatformData();
	static std::vector<DoorData> initializeDoorData();
	static std::vector<ViewAreaData> initializeViewAreaData();
	static std::map<Scenes, std::vector<SceneElement*>> initializeSceneData();
};


#endif