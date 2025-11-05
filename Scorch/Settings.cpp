#include "Settings.h"

int Settings::FontSizeS = 12;
int Settings::FontSizeM = 16;
int Settings::FontSizeL = 24;

int Settings::DefaultFontSizeS = 12;
int Settings::DefaultFontSizeM = 16;
int Settings::DefaultFontSizeL = 24;

double Settings::FontScalar = 1;

sf::Vector2f Settings::DefaultWindowSize(1000,750);

void Settings::updateFontSize(sf::Vector2u windowSize)
{
	if (windowSize.x / DefaultWindowSize.x < windowSize.y / DefaultWindowSize.y) {
		FontSizeS = windowSize.x / DefaultWindowSize.x * FontScalar * DefaultFontSizeS;
		FontSizeM = windowSize.x / DefaultWindowSize.x * FontScalar * DefaultFontSizeM;
		FontSizeL = windowSize.x / DefaultWindowSize.x * FontScalar * DefaultFontSizeL;
	}
	else{
		FontSizeS = windowSize.y / DefaultWindowSize.y * FontScalar * DefaultFontSizeS;
		FontSizeM = windowSize.y / DefaultWindowSize.y * FontScalar * DefaultFontSizeM;
		FontSizeL = windowSize.y / DefaultWindowSize.y * FontScalar * DefaultFontSizeL;
	}
}
