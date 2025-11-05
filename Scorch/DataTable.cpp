#include "DataTable.h"
#include "Categories.hpp"
#include <iostream>
#include <vector>
#include <fstream>

//Document DATATABLE::JSONDATA;
const std::string DATATABLE::JSON_FILEPATH = "data/SceneData.json";

std::vector<EntityData> DATATABLE::entityData = initializeEntityData();
std::vector<PlatformData> DATATABLE::platformData = initializePlatformData();
std::vector<AnimationData> DATATABLE::animationData = initializeAnimationData();
std::vector<AnimatedPlatformData>	DATATABLE::animatedPlatformData = initializeAnimatedPlatformData();
std::vector<FallingPlatformData> DATATABLE::fallingPlatformData = initializeFallingPlatformData();
std::vector<MovingPlatformData> DATATABLE::movingPlatformData = initializeMovingPlatformData();
std::vector<DoorData>	DATATABLE::doorData = initializeDoorData();
std::vector<ViewAreaData> DATATABLE::viewData = initializeViewAreaData();
std::map<Scenes, std::vector<SceneElement*>> DATATABLE::SceneData = initializeSceneData();

// For std::bind() placeholders _1, _2, ...
using namespace std::placeholders;

void DATATABLE::prepareJsonFile()
{
	std::ifstream JsonFile(JSON_FILEPATH);
	if (!JsonFile.is_open()) {
		std::cout << "failed to open JsonFile!!!\n";
		return;
	}
	else {
		std::cout << "opened file!!!\n";
	}

	IStreamWrapper JsonFileWrapper(JsonFile);
	//DATATABLE::JSONDATA.ParseStream(JsonFileWrapper);
}

void DATATABLE::prepareData()
{
	sf::Clock c;
	while (c.getElapsedTime() <= sf::seconds(2)) {

	}
}

std::vector<EntityData> DATATABLE::initializeEntityData()
{
	std::vector<EntityData> data(Category::TypeCount);

	return data;
}

std::vector<AnimationData> DATATABLE::initializeAnimationData()
{
	std::vector<AnimationData> data(DataRetrivalType::AnimationsTypeCount);

	data[DataRetrivalType::Test].mDuration = sf::seconds(2);
	data[DataRetrivalType::Test].mFrameSize = sf::Vector2i(80,80);
	data[DataRetrivalType::Test].mNumFrames = 3;
	data[DataRetrivalType::Test].mRepeat = true;

	data[DataRetrivalType::FallingSand].mDuration = sf::seconds(0.2f);
	data[DataRetrivalType::FallingSand].mFrameSize = sf::Vector2i(160, 40);
	data[DataRetrivalType::FallingSand].mNumFrames = 5;
	data[DataRetrivalType::FallingSand].mRepeat = false;

	return data;
}

std::vector<PlatformData> DATATABLE::initializePlatformData()
{
	std::vector<PlatformData> data(DataRetrivalType::PlatformsTypeCount);

	
	data[DataRetrivalType::Platform].friction = 20;
	data[DataRetrivalType::Platform].texture = Textures::Platform;

	data[DataRetrivalType::Animated].friction = 20;
	data[DataRetrivalType::Animated].texture = Textures::TestAnimation;

	data[DataRetrivalType::Falling].friction = 20;
	data[DataRetrivalType::Falling].texture = Textures::FallingSand;

	data[DataRetrivalType::Moving].friction = 20;
	data[DataRetrivalType::Moving].texture = Textures::Platform;

	data[DataRetrivalType::SandPlatform].friction = 20;
	data[DataRetrivalType::SandPlatform].texture = Textures::Sand;

	data[DataRetrivalType::SandAnimatedFalling].friction = 20;
	data[DataRetrivalType::SandAnimatedFalling].texture = Textures::FallingSand;

	return data;
};

std::vector<AnimatedPlatformData> DATATABLE::initializeAnimatedPlatformData()
{
	std::vector<AnimatedPlatformData> data(DataRetrivalType::PlatformsTypeCount);

	std::vector<PlatformData> platformData = initializePlatformData();
	std::vector<AnimationData> animationData = initializeAnimationData();

	data[DataRetrivalType::Animated].platform = platformData[DataRetrivalType::Animated];
	data[DataRetrivalType::Animated].animation = animationData[DataRetrivalType::Test];
	
	return data;
};

std::vector<FallingPlatformData> DATATABLE::initializeFallingPlatformData() {
	std::vector<FallingPlatformData> data(DataRetrivalType::PlatformsTypeCount);

	std::vector<PlatformData> platformData = initializePlatformData();
	std::vector<AnimationData> animationData = initializeAnimationData();

	data[DataRetrivalType::Falling].platform = platformData[DataRetrivalType::Falling];
	data[DataRetrivalType::Falling].animation = animationData[DataRetrivalType::Falling];
	data[DataRetrivalType::Falling].resetTime = sf::seconds(999999);

	data[DataRetrivalType::SandAnimatedFalling].platform = platformData[DataRetrivalType::SandAnimatedFalling];
	data[DataRetrivalType::SandAnimatedFalling].animation = animationData[DataRetrivalType::FallingSand];
	data[DataRetrivalType::SandAnimatedFalling].resetTime = sf::seconds(5);

	return data;
};

std::vector<MovingPlatformData> DATATABLE::initializeMovingPlatformData() {
	std::vector<MovingPlatformData> data(DataRetrivalType::PlatformsTypeCount);

	std::vector<PlatformData> platformData = initializePlatformData();

	data[DataRetrivalType::Moving].platform = platformData[DataRetrivalType::Moving];
	data[DataRetrivalType::Moving].startingPoint = sf::Vector2i(0,0);
	data[DataRetrivalType::Moving].endPoint = sf::Vector2i(200,200);
	data[DataRetrivalType::Moving].speed = sf::Vector2f(2,2);

	data[DataRetrivalType::Moving2].platform = platformData[DataRetrivalType::Moving];
	data[DataRetrivalType::Moving2].startingPoint = sf::Vector2i(0, 0);
	data[DataRetrivalType::Moving2].endPoint = sf::Vector2i(200, 0);
	data[DataRetrivalType::Moving2].speed = sf::Vector2f(2, 2);
	

	return data;
};

std::vector<DoorData> DATATABLE::initializeDoorData() {
	std::vector<DoorData> data(DataRetrivalType::DoorsTypeCount);

	data[DataRetrivalType::DoorToHome].texture = Textures::Door;
	data[DataRetrivalType::DoorToHome].arrowTexture = Textures::DoorArrow;
	data[DataRetrivalType::DoorToHome].playerPos = sf::Vector2f(800, 650);

	data[DataRetrivalType::DoorOutHome].texture = Textures::Door;
	data[DataRetrivalType::DoorOutHome].arrowTexture = Textures::DoorArrow;
	data[DataRetrivalType::DoorOutHome].playerPos = sf::Vector2f(800, 650);

	return data;
};

std::vector<ViewAreaData> DATATABLE::initializeViewAreaData()
{
	std::vector<ViewAreaData> data(DataRetrivalType::ViewAreasTypeCount);

	data[DataRetrivalType::TestViewArea].area = sf::FloatRect({ 0, 0 }, { 200, 1000 });
	data[DataRetrivalType::TestViewArea].viewSize = sf::Vector2f(800, 600);
	data[DataRetrivalType::TestViewArea].lockView = false;
	data[DataRetrivalType::TestViewArea].viewCenter = sf::Vector2f();

	data[DataRetrivalType::Test2ViewArea].area = sf::FloatRect({ 0, 0 }, { 200, 1000 });
	data[DataRetrivalType::Test2ViewArea].viewSize = sf::Vector2f(1200, 900);
	data[DataRetrivalType::Test2ViewArea].lockView = true;
	data[DataRetrivalType::Test2ViewArea].viewCenter = sf::Vector2f(400, 400);

	return data;
}

std::map<Scenes, std::vector<SceneElement*>> DATATABLE::initializeSceneData()
{
	return std::map<Scenes, std::vector<SceneElement*>>();
}
