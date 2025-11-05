#pragma once
#include <SFML/Graphics/Rect.hpp>

class Settings {
public:
	static void updateFontSize(sf::Vector2u windowSize);
	
	static int FontSizeS;
	static int FontSizeM;
	static int FontSizeL;

	static int DefaultFontSizeS;
	static int DefaultFontSizeM;
	static int DefaultFontSizeL;

	static double FontScalar; //WindowPixels * FontScalar * DefaultFontSizeX = FontSizeX

	static sf::Vector2f DefaultWindowSize;
};