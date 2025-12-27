#pragma once

#ifndef DataTable_hpp
#define DataTable_hpp

#include "Scenes.h"
#include "ResourceIdentifiers.hpp"
#include "Scene_Builder.h"
#include "DataRetrivalTypes.h"

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>

#include <vector>
#include <functional>

#include "nlohmann/json.hpp"
using json = nlohmann::json;

//Updated minimally after Initialization. 
//Look to settings for Application-updated consts (which ig means their not consts...)
class DATATABLE {
public:
	static void loadScene(Scenes s);
	static void offloadScene(Scenes s);

	static void loadEntityData();

	static void loadSaveFile(int n);

	static void loadResourceLocations();

	static std::map<Scenes, json> SCENE_DATA;
	static json ENTITY_DATA;
	static json SAVE_DATA;

	static std::map<Scenes, std::string> SCENE_FILE_NAMES;
	static std::map<std::string, std::string> RESOURCE_LOCATIONS;
};


#endif