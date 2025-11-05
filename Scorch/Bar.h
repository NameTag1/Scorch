#pragma once

#include "Component.hpp"
#include "ResourceIdentifiers.hpp"
#include "ResourceHolder.hpp"

#include <memory>
#include <SFML/Graphics.hpp>

namespace GUI
{

class Bar : public Component
{
public:
    typedef std::shared_ptr<Bar> Ptr;


public:
    Bar();

    virtual bool		isSelectable() const;
    void				setMessure(float max, float current);

    virtual void		handleEvent(const sf::Event& event);

    virtual void            updateRect(sf::FloatRect parrentRect);

private:
    void				draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    float               mMax;
    float               mCurrent;

    sf::RectangleShape  mMaxBar;
    sf::RectangleShape  mCurrentBar;

};

}

