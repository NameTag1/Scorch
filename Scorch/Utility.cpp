#include "Utility.hpp"

#include "Settings.h"
#include "Logger.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include <random>
#include <cmath>
#include <ctime>
#include <cassert>


namespace
{
	std::default_random_engine createRandomEngine()
	{
		auto seed = static_cast<unsigned long>(std::time(nullptr));
		return std::default_random_engine(seed);
	}

	auto RandomEngine = createRandomEngine();
}

std::string toString(sf::Keyboard::Key key)
{
	#define KEYTOSTRING_CASE(KEY) case sf::Keyboard::KEY: return #KEY;

	switch (key)
	{
		KEYTOSTRING_CASE(Unknown)
		KEYTOSTRING_CASE(A)
		KEYTOSTRING_CASE(B)
		KEYTOSTRING_CASE(C)
		KEYTOSTRING_CASE(D)
		KEYTOSTRING_CASE(E)
		KEYTOSTRING_CASE(F)
		KEYTOSTRING_CASE(G)
		KEYTOSTRING_CASE(H)
		KEYTOSTRING_CASE(I)
		KEYTOSTRING_CASE(J)
		KEYTOSTRING_CASE(K)
		KEYTOSTRING_CASE(L)
		KEYTOSTRING_CASE(M)
		KEYTOSTRING_CASE(N)
		KEYTOSTRING_CASE(O)
		KEYTOSTRING_CASE(P)
		KEYTOSTRING_CASE(Q)
		KEYTOSTRING_CASE(R)
		KEYTOSTRING_CASE(S)
		KEYTOSTRING_CASE(T)
		KEYTOSTRING_CASE(U)
		KEYTOSTRING_CASE(V)
		KEYTOSTRING_CASE(W)
		KEYTOSTRING_CASE(X)
		KEYTOSTRING_CASE(Y)
		KEYTOSTRING_CASE(Z)
		KEYTOSTRING_CASE(Num0)
		KEYTOSTRING_CASE(Num1)
		KEYTOSTRING_CASE(Num2)
		KEYTOSTRING_CASE(Num3)
		KEYTOSTRING_CASE(Num4)
		KEYTOSTRING_CASE(Num5)
		KEYTOSTRING_CASE(Num6)
		KEYTOSTRING_CASE(Num7)
		KEYTOSTRING_CASE(Num8)
		KEYTOSTRING_CASE(Num9)
		KEYTOSTRING_CASE(Escape)
		KEYTOSTRING_CASE(LControl)
		KEYTOSTRING_CASE(LShift)
		KEYTOSTRING_CASE(LAlt)
		KEYTOSTRING_CASE(LSystem)
		KEYTOSTRING_CASE(RControl)
		KEYTOSTRING_CASE(RShift)
		KEYTOSTRING_CASE(RAlt)
		KEYTOSTRING_CASE(RSystem)
		KEYTOSTRING_CASE(Menu)
		KEYTOSTRING_CASE(LBracket)
		KEYTOSTRING_CASE(RBracket)
		KEYTOSTRING_CASE(SemiColon)
		KEYTOSTRING_CASE(Comma)
		KEYTOSTRING_CASE(Period)
		KEYTOSTRING_CASE(Quote)
		KEYTOSTRING_CASE(Slash)
		KEYTOSTRING_CASE(BackSlash)
		KEYTOSTRING_CASE(Tilde)
		KEYTOSTRING_CASE(Equal)
		KEYTOSTRING_CASE(Dash)
		KEYTOSTRING_CASE(Space)
		KEYTOSTRING_CASE(Return)
		KEYTOSTRING_CASE(BackSpace)
		KEYTOSTRING_CASE(Tab)
		KEYTOSTRING_CASE(PageUp)
		KEYTOSTRING_CASE(PageDown)
		KEYTOSTRING_CASE(End)
		KEYTOSTRING_CASE(Home)
		KEYTOSTRING_CASE(Insert)
		KEYTOSTRING_CASE(Delete)
		KEYTOSTRING_CASE(Add)
		KEYTOSTRING_CASE(Subtract)
		KEYTOSTRING_CASE(Multiply)
		KEYTOSTRING_CASE(Divide)
		KEYTOSTRING_CASE(Left)
		KEYTOSTRING_CASE(Right)
		KEYTOSTRING_CASE(Up)
		KEYTOSTRING_CASE(Down)
		KEYTOSTRING_CASE(Numpad0)
		KEYTOSTRING_CASE(Numpad1)
		KEYTOSTRING_CASE(Numpad2)
		KEYTOSTRING_CASE(Numpad3)
		KEYTOSTRING_CASE(Numpad4)
		KEYTOSTRING_CASE(Numpad5)
		KEYTOSTRING_CASE(Numpad6)
		KEYTOSTRING_CASE(Numpad7)
		KEYTOSTRING_CASE(Numpad8)
		KEYTOSTRING_CASE(Numpad9)
		KEYTOSTRING_CASE(F1)
		KEYTOSTRING_CASE(F2)
		KEYTOSTRING_CASE(F3)
		KEYTOSTRING_CASE(F4)
		KEYTOSTRING_CASE(F5)
		KEYTOSTRING_CASE(F6)
		KEYTOSTRING_CASE(F7)
		KEYTOSTRING_CASE(F8)
		KEYTOSTRING_CASE(F9)
		KEYTOSTRING_CASE(F10)
		KEYTOSTRING_CASE(F11)
		KEYTOSTRING_CASE(F12)
		KEYTOSTRING_CASE(F13)
		KEYTOSTRING_CASE(F14)
		KEYTOSTRING_CASE(F15)
		KEYTOSTRING_CASE(Pause)
	}

	return "";
}

void centerOrigin(sf::Sprite& sprite)
{
	sf::FloatRect bounds = sprite.getLocalBounds();
	sprite.setOrigin(std::floor(bounds.left + bounds.width / 2.f), std::floor(bounds.top + bounds.height / 2.f));
}

void centerOrigin(sf::Text& text)
{
	sf::FloatRect bounds = text.getLocalBounds();
	text.setOrigin(std::floor(bounds.left + bounds.width / 2.f), std::floor(bounds.top + bounds.height / 2.f));
}

float toDegree(float radian)
{
	return 180.f / 3.141592653589793238462643383f * radian;
}

float toRadian(float degree)
{
	return 3.141592653589793238462643383f / 180.f * degree;
}

int randomInt(int exclusiveMax)
{
	std::uniform_int_distribution<> distr(0, exclusiveMax - 1);
	return distr(RandomEngine);
}

float length(sf::Vector2f vector)
{
	return std::sqrt(vector.x * vector.x + vector.y * vector.y);
}

sf::Vector2f unitVector(sf::Vector2f vector)
{
	assert(vector != sf::Vector2f(0.f, 0.f));
	return vector / length(vector);
}

float adjustToZero(float i, float adjustment) {
	if (i > -adjustment && i < adjustment) {
		i = 0;
	}
	else if (i < 0) {
		i += adjustment;
	}
	else if (i > 0) {
		i -= adjustment;
	}
	return i;
};

float adjustToNumber(float i, float adjustment, float number) {
	if (i > -adjustment + number && i < adjustment + number) {
		i = number;
	}
	else if (i < number) {
		i += adjustment;
	}
	else if (i > number) {
		i -= adjustment;
	}
	return i;
}

bool matchesCategories(SceneNode::Pair& colliders, Category::Type type1, Category::Type type2) {
	std::vector<unsigned int> category1 = colliders.first->getCategory();
	std::vector<unsigned int> category2 = colliders.second->getCategory();

	for (auto i : category1) {
		for (auto g : category2) {
			if (type1 == i && type2 == g) {
				return true;
			}
			else if (type1 == g && type2 == i) {
				std::swap(colliders.first, colliders.second);
				return true;
			}
		}
	}
	return false;
}

bool matchesCategory(SceneNode& item, Category::Type type)
{
	std::vector<unsigned int> category = item.getCategory();
	for (auto g : category) {
		if (type == g) {
			return true;
		}
	}
	return false;
}

bool matchesCategory(std::vector<unsigned int> category, Category::Type type)
{
	for (auto g : category) {
		if (type == g) {
			return true;
		}
	}
	return false;
}

template<typename TargetPtr, typename SourcePtr>
inline TargetPtr safeCast(SourcePtr source)
{
	// 1. Ensure at compile-time that the user is passing pointer types
	static_assert(std::is_pointer<TargetPtr>::value, "safeCast target must be a pointer type.");
	static_assert(std::is_pointer<SourcePtr>::value, "safeCast source must be a pointer type.");

	// 2. Perform the cast safely
	if (TargetPtr castedPtr = dynamic_cast<TargetPtr>(source)) {
		return castedPtr;
	}

	// 3. If it fails, log it. If source is null, log that; otherwise, get the true dynamic object type.
	if (source != nullptr) {
		std::string sourceDynamicName = typeid(*source).name(); // Use *source to extract the actual dynamic type
		std::string targetName = typeid(typename std::remove_pointer<TargetPtr>::type).name();

		Logger::Instance->LogData(Logger::Action,
			"Utility::safeCast: Failed to cast dynamic type " + sourceDynamicName + " to " + targetName);
	}
	else {
		Logger::Instance->LogData(Logger::Action, "Utility::safeCast: Attempted to cast a nullptr.");
	}

	return nullptr;
}

Scenes stringToScene(std::string i) {
	if (i == "Null") {
		return Null;
	}
	if (i == "Test") {
		return Test;
	}
	if (i == "Test2") {
		return Test2;
	}
	if (i == "Sietch") {
		return Sietch;
	}
	if (i == "Home") {
		return Home;
	}
	if (i == "Dunes") {
		return Dunes;
	}
	if (i == "MagmaFields") {
		return MagmaFields;
	}
	if (i == "Canyons") {
		return Canyons;
	}
	return Null;
}

float pixelToMeter(float pixels)
{
	return pixels / Settings::MtPConversionRate;
}

sf::Vector2f pixelToMeter(sf::Vector2f pixels)
{
	return pixels / Settings::MtPConversionRate;
}

float meterToPixel(float meters)
{
	return meters * Settings::MtPConversionRate;
}

sf::Vector2f meterToPixel(sf::Vector2f meters)
{
	return meters * Settings::MtPConversionRate;
}
