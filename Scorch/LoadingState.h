#pragma once

#include "State.hpp"
#include "Scene_Builder.h"
#include "World.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>


#include <thread>


class LoadingState : public State
{
public:
	LoadingState(StateStack& stack, Context context);

	~LoadingState();

	void				BeginLoading();

	virtual void		draw();
	virtual bool		update(sf::Time dt);
	virtual bool		handleEvent(const sf::Event& event);

private:
	sf::Text loadingText;
	Scene_Builder* builder;
	World* world;
	sf::Clock mTimer;
	sf::Time loadingDuration;
	std::thread mThread;
	bool mThreadDone;
};

