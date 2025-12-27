#pragma once
#include "Weapon.h"

Weapon* createWeapon(const TextureHolder& textures, json data);
Category::Type parseCategoryType(const std::string& categoryStr);