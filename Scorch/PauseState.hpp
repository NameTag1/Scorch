#ifndef Pausestate_hpp
#define Pausestate_hpp


#include "State.hpp"
#include "Container.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>


class PauseState : public State
{
	public:
							PauseState(StateStack& stack, Context context);

		virtual void		draw();
		virtual bool		update(sf::Time dt);
		virtual bool		handleEvent(const sf::Event& event);


	private:
		sf::Sprite			mBackgroundSprite;
		GUI::Container 		mGUIContainer;
		GUI::Container 		mPlayerGUIContainer;
		Context				mSavedContext;
};

#endif // BOOK_PAUSESTATE_HPP