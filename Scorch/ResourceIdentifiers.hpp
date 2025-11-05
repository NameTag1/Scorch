#ifndef Resource_Identifiers_hpp
#define Resource_Identifiers_hpp


// Forward declaration of SFML classes
namespace sf
{
	class Texture;
	class Font;
}

namespace Textures
{
	enum ID
	{
		None,
		Default,
		Background,
		Background2,
		TitleScreen,
		ButtonNormal,
		ButtonSelected,
		ButtonPressed,
		Black,

		Player,
		Enemy,
		Platform,
		TestAnimation,
		Sand,
		
		Door,
		DoorArrow,
		FallingSand,
		
		Slash,
		Greatsword
	};
}

namespace Fonts
{
	enum ID
	{
		Main,
	};
}

// Forward declaration and a few type definitions
template <typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, Textures::ID>	TextureHolder;
typedef ResourceHolder<sf::Font, Fonts::ID>			FontHolder;

#endif // BOOK_RESOURCEIDENTIFIERS_HPP
