#ifndef Utility_hpp
#define Utility_hpp

#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Vector2.hpp>

#include <sstream>
#include "SceneNode.hpp"
#include "Scenes.h"

namespace sf
{
	class Sprite;
	class Text;
}

// Since std::to_string doesn't work on MinGW we have to implement
// our own to support all platforms.
template <typename T>
std::string toString(const T& value);

// Convert enumerators to strings
std::string toString(sf::Keyboard::Key key);

// Call setOrigin() with the center of the object
void centerOrigin(sf::Sprite& sprite);
void centerOrigin(sf::Text& text);

float toDegree(float radian);
float toRadian(float degree);

int randomInt(int exclusiveMax);

float length(sf::Vector2f vector);
sf::Vector2f unitVector(sf::Vector2f vector);

float adjustToZero(float i, float adjustment);
float adjustToNumber(float i, float adjustment, float number);

bool matchesCategories(SceneNode::Pair& colliders, Category::Type type1, Category::Type type2);
bool matchesCategory(SceneNode& item, Category::Type type);

template <typename T>
bool contains(const std::vector<T>& vec, const T& item);

Scenes stringToScene(std::string i);

float pixelToMeter(float pixels);
sf::Vector2f pixelToMeter(sf::Vector2f pixels);

float meterToPixel(float meters);
sf::Vector2f meterToPixel(sf::Vector2f meters);

#include "Utility.inl"
#endif