#ifndef Component_hpp
#define Component_hpp

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>

#include <memory>
#include "RelativeRect.h"


namespace sf
{
	class Event;
}

namespace GUI
{

class Component : public sf::Drawable, public sf::Transformable
{
    public:
        typedef std::shared_ptr<Component> Ptr;

	public:
							Component();
        virtual				~Component();

        virtual bool		isSelectable() const = 0;
		bool				isSelected() const;
        virtual void		select();
        virtual void		deselect();

        virtual bool		isActive() const;
        virtual void		activate();
        virtual void		deactivate();

        virtual void		handleEvent(const sf::Event& event) = 0;

        virtual void        setRelativeRect(RelativeRect rect);
        virtual void        updateRect(sf::FloatRect parrentRect);
        virtual sf::FloatRect getRect();

    protected:
        RelativeRect        mRect;

    private:
        bool				mIsSelected;
        bool				mIsActive;
};

}

#endif
