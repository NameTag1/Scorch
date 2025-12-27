#include "WeaponBuilder.h"

#include "Logger.h"

#include "Greatsword.h"

Weapon* createWeapon(const TextureHolder& textures, json data)
{
	if (data.contains("Type") && data["Type"].is_string()) {
		std::string typeStr = data["Type"].get<std::string>();
		Category::Type type = parseCategoryType(data["Category"]);
		if (typeStr == "Greatsword") {
			return new Greatsword(textures, type);
		}
		else {
			Logger::Instance->LogData(Logger::Action, "Weapon creation failed: Unknown weapon type.");
			return nullptr;
		}
	}
	else {
		Logger::Instance->LogData(Logger::Action, "Weapon creation failed: 'Type' field missing or not a string.");
		return nullptr;
	}
}

Category::Type parseCategoryType(const std::string& categoryStr)
{
	if (categoryStr == "Enemy") {
		return Category::Enemy;
	}
	else if (categoryStr == "Player") {
		return Category::Player;
	}
	else {
		return Category::None;
	}
}
