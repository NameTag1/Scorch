#ifndef Utility_hpp
#define Utility_hpp

#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Vector2.hpp>

#include <sstream>
#include "SceneNode.hpp"


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

double adjustToZero(double i, double adjustment);
double adjustToNumber(double i, double adjustment, double number);

bool matchesCategories(SceneNode::Pair& colliders, Category::Type type1, Category::Type type2);
bool matchesCategory(SceneNode& item, Category::Type type);

#include "Utility.inl"
#endif