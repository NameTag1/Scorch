#ifndef SpriteNode_hpp
#define SpriteNode_hpp


#include "SceneNode.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics.hpp>


class SpriteNode : public SceneNode
{
	public:
		explicit			SpriteNode(const sf::Texture& texture);
							SpriteNode(const sf::Texture& texture, const sf::IntRect& textureRect);


	private:
		virtual void		drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;


	private:
		sf::Sprite			mSprite;
};

#endif // BOOK_SPRITENODE_HPP
