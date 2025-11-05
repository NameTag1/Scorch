#ifndef Image_hpp
#define Image_hpp

#include "Component.hpp"
#include "ResourceIdentifiers.hpp"
#include "ResourceHolder.hpp"

#include <memory>
#include <SFML/Graphics.hpp>

namespace GUI
{

    class Image : public Component
    {
    public:
        typedef std::shared_ptr<Image> Ptr;


    public:
        Image(const TextureHolder& textures, Textures::ID id);

        void                updateImage(const TextureHolder& textures, Textures::ID id);

        virtual bool		isSelectable() const;
       
        virtual void		handleEvent(const sf::Event& event);

        virtual void        updateRect(sf::FloatRect parrentRect);

    private:
        void				draw(sf::RenderTarget& target, sf::RenderStates states) const;


    private:
        sf::Sprite				mSprite;
    };

}

#endif
