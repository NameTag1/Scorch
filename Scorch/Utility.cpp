#include "Utility.hpp"

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
	#define BOOK_KEYTOSTRING_CASE(KEY) case sf::Keyboard::KEY: return #KEY;

	switch (key)
	{
		BOOK_KEYTOSTRING_CASE(Unknown)
		BOOK_KEYTOSTRING_CASE(A)
		BOOK_KEYTOSTRING_CASE(B)
		BOOK_KEYTOSTRING_CASE(C)
		BOOK_KEYTOSTRING_CASE(D)
		BOOK_KEYTOSTRING_CASE(E)
		BOOK_KEYTOSTRING_CASE(F)
		BOOK_KEYTOSTRING_CASE(G)
		BOOK_KEYTOSTRING_CASE(H)
		BOOK_KEYTOSTRING_CASE(I)
		BOOK_KEYTOSTRING_CASE(J)
		BOOK_KEYTOSTRING_CASE(K)
		BOOK_KEYTOSTRING_CASE(L)
		BOOK_KEYTOSTRING_CASE(M)
		BOOK_KEYTOSTRING_CASE(N)
		BOOK_KEYTOSTRING_CASE(O)
		BOOK_KEYTOSTRING_CASE(P)
		BOOK_KEYTOSTRING_CASE(Q)
		BOOK_KEYTOSTRING_CASE(R)
		BOOK_KEYTOSTRING_CASE(S)
		BOOK_KEYTOSTRING_CASE(T)
		BOOK_KEYTOSTRING_CASE(U)
		BOOK_KEYTOSTRING_CASE(V)
		BOOK_KEYTOSTRING_CASE(W)
		BOOK_KEYTOSTRING_CASE(X)
		BOOK_KEYTOSTRING_CASE(Y)
		BOOK_KEYTOSTRING_CASE(Z)
		BOOK_KEYTOSTRING_CASE(Num0)
		BOOK_KEYTOSTRING_CASE(Num1)
		BOOK_KEYTOSTRING_CASE(Num2)
		BOOK_KEYTOSTRING_CASE(Num3)
		BOOK_KEYTOSTRING_CASE(Num4)
		BOOK_KEYTOSTRING_CASE(Num5)
		BOOK_KEYTOSTRING_CASE(Num6)
		BOOK_KEYTOSTRING_CASE(Num7)
		BOOK_KEYTOSTRING_CASE(Num8)
		BOOK_KEYTOSTRING_CASE(Num9)
		BOOK_KEYTOSTRING_CASE(Escape)
		BOOK_KEYTOSTRING_CASE(LControl)
		BOOK_KEYTOSTRING_CASE(LShift)
		BOOK_KEYTOSTRING_CASE(LAlt)
		BOOK_KEYTOSTRING_CASE(LSystem)
		BOOK_KEYTOSTRING_CASE(RControl)
		BOOK_KEYTOSTRING_CASE(RShift)
		BOOK_KEYTOSTRING_CASE(RAlt)
		BOOK_KEYTOSTRING_CASE(RSystem)
		BOOK_KEYTOSTRING_CASE(Menu)
		BOOK_KEYTOSTRING_CASE(LBracket)
		BOOK_KEYTOSTRING_CASE(RBracket)
		BOOK_KEYTOSTRING_CASE(SemiColon)
		BOOK_KEYTOSTRING_CASE(Comma)
		BOOK_KEYTOSTRING_CASE(Period)
		BOOK_KEYTOSTRING_CASE(Quote)
		BOOK_KEYTOSTRING_CASE(Slash)
		BOOK_KEYTOSTRING_CASE(BackSlash)
		BOOK_KEYTOSTRING_CASE(Tilde)
		BOOK_KEYTOSTRING_CASE(Equal)
		BOOK_KEYTOSTRING_CASE(Dash)
		BOOK_KEYTOSTRING_CASE(Space)
		BOOK_KEYTOSTRING_CASE(Return)
		BOOK_KEYTOSTRING_CASE(BackSpace)
		BOOK_KEYTOSTRING_CASE(Tab)
		BOOK_KEYTOSTRING_CASE(PageUp)
		BOOK_KEYTOSTRING_CASE(PageDown)
		BOOK_KEYTOSTRING_CASE(End)
		BOOK_KEYTOSTRING_CASE(Home)
		BOOK_KEYTOSTRING_CASE(Insert)
		BOOK_KEYTOSTRING_CASE(Delete)
		BOOK_KEYTOSTRING_CASE(Add)
		BOOK_KEYTOSTRING_CASE(Subtract)
		BOOK_KEYTOSTRING_CASE(Multiply)
		BOOK_KEYTOSTRING_CASE(Divide)
		BOOK_KEYTOSTRING_CASE(Left)
		BOOK_KEYTOSTRING_CASE(Right)
		BOOK_KEYTOSTRING_CASE(Up)
		BOOK_KEYTOSTRING_CASE(Down)
		BOOK_KEYTOSTRING_CASE(Numpad0)
		BOOK_KEYTOSTRING_CASE(Numpad1)
		BOOK_KEYTOSTRING_CASE(Numpad2)
		BOOK_KEYTOSTRING_CASE(Numpad3)
		BOOK_KEYTOSTRING_CASE(Numpad4)
		BOOK_KEYTOSTRING_CASE(Numpad5)
		BOOK_KEYTOSTRING_CASE(Numpad6)
		BOOK_KEYTOSTRING_CASE(Numpad7)
		BOOK_KEYTOSTRING_CASE(Numpad8)
		BOOK_KEYTOSTRING_CASE(Numpad9)
		BOOK_KEYTOSTRING_CASE(F1)
		BOOK_KEYTOSTRING_CASE(F2)
		BOOK_KEYTOSTRING_CASE(F3)
		BOOK_KEYTOSTRING_CASE(F4)
		BOOK_KEYTOSTRING_CASE(F5)
		BOOK_KEYTOSTRING_CASE(F6)
		BOOK_KEYTOSTRING_CASE(F7)
		BOOK_KEYTOSTRING_CASE(F8)
		BOOK_KEYTOSTRING_CASE(F9)
		BOOK_KEYTOSTRING_CASE(F10)
		BOOK_KEYTOSTRING_CASE(F11)
		BOOK_KEYTOSTRING_CASE(F12)
		BOOK_KEYTOSTRING_CASE(F13)
		BOOK_KEYTOSTRING_CASE(F14)
		BOOK_KEYTOSTRING_CASE(F15)
		BOOK_KEYTOSTRING_CASE(Pause)
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

double adjustToZero(double i, double adjustment) {
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

double adjustToNumber(double i, double adjustment, double number) {
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

