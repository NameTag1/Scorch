#include "DataTable.h"
#include "Categories.hpp"
#include <vector>
#include <fstream>

#include "Logger.h"

#include "nlohmann/json.hpp"
using json = nlohmann::json;

std::map<Scenes, json> DATATABLE::SCENE_DATA;
std::map<Scenes, std::string> DATATABLE::SCENE_FILE_NAMES;
json DATATABLE::ENTITY_DATA;
json DATATABLE::SAVE_DATA;

std::map<std::string, std::string> DATATABLE::RESOURCE_LOCATIONS;

// For std::bind() placeholders _1, _2, ...
using namespace std::placeholders;

void DATATABLE::loadScene(Scenes s)
{
	SCENE_FILE_NAMES.clear();
	SCENE_FILE_NAMES.insert({ Scenes::Test, "data/SceneData.json" });
	SCENE_FILE_NAMES.insert({ Scenes::Test2, "data/SceneData2.json" });	

	std::ifstream JsonFileWrapper(SCENE_FILE_NAMES[s]);
	if (!JsonFileWrapper) {
		Logger::Instance->LogData(Logger::Action, "Failed to Load: " + SCENE_FILE_NAMES[s]);
		return;
	}
	else {
		Logger::Instance->LogData(Logger::Action, "Loaded: " + SCENE_FILE_NAMES[s]);
	}
	JsonFileWrapper >> SCENE_DATA[s];
}

void DATATABLE::offloadScene(Scenes s)
{
	//SCENE_DATA.erase(s);
}

void DATATABLE::loadResourceLocations()
{
	std::ifstream JsonFileWrapper("data/ResourceLocations.json");
	if (!JsonFileWrapper) {
		Logger::Instance->LogData(Logger::Action, "Failed to Load: data/ResourceLocations.json");
		return;
	}
	else {
		Logger::Instance->LogData(Logger::Action, "Loaded: data/ResourceLocations.json");
	}
	json doc;
	JsonFileWrapper >> doc;

	for (auto& item : doc.items()) {
		RESOURCE_LOCATIONS[std::string(item.key())] = "resources/" + std::string(item.value());
	}
}

void DATATABLE::loadEntityData()
{
	std::ifstream JsonFileWrapper("data/EntityData.json");
	if (!JsonFileWrapper) {
		Logger::Instance->LogData(Logger::Action, "Failed to Load: data/EntityData.json");
		return;
	}
	else {
		Logger::Instance->LogData(Logger::Action, "Loaded: data/EntityData.json");
	}
	JsonFileWrapper >> ENTITY_DATA;
}

void DATATABLE::loadSaveFile(int n)
{
	std::string i = "data/Save" + std::to_string(n) + ".json";
	std::ifstream JsonFileWrapper(i);
	if (!JsonFileWrapper) {
		Logger::Instance->LogData(Logger::Action, "Failed to Load: " + i);
		return;
	}
	else {
		Logger::Instance->LogData(Logger::Action, "Loaded: " + i);
	}
	JsonFileWrapper >> SAVE_DATA;
}
