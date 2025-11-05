#include "Application.hpp"
#include "State.hpp"
#include "States.hpp"
#include "TitleState.hpp"
#include "GameState.hpp"
#include "MenuState.hpp"
#include "PauseState.hpp"
#include "SettingsState.hpp"
#include "Utility.hpp"
#include "LoadingState.h"
#include "Settings.h"

#include <iostream>
#include "OverlayState.h"

const sf::Time Application::TimePerFrame = sf::seconds(1.f/60.f);

Application::Application()
: mWindow(sf::VideoMode({ Settings::DefaultWindowSize.x, Settings::DefaultWindowSize.y }), "Scorch", sf::Style::Default)
, mTextures()
, mFonts()
, mPlayer()
, mStateStack(State::Context(mWindow, mTextures, mFonts, mPlayer))
, mStatisticsText()
, mStatisticsUpdateTime()
, mStatisticsNumFrames(0)
, mScreenRatio(4,3) //4/3 ratio
{
	mWindow.setKeyRepeatEnabled(false);

	mFonts.load(Fonts::Main, "resources/montserrat/Montserrat-Regular.ttf");

	mTextures.load(Textures::TitleScreen,		"resources/Title_Screen.jpg");
	mTextures.load(Textures::ButtonNormal,		"resources/ButtonNormal.png");
	mTextures.load(Textures::ButtonSelected,	"resources/ButtonSelected.png");
	mTextures.load(Textures::ButtonPressed,		"resources/ButtonPressed.png");
	mTextures.load(Textures::Black,				"resources/Black.bmp");

	mStatisticsText.setFont(mFonts.get(Fonts::Main));
	mStatisticsText.setPosition({ 5.f, 5.f });
	mStatisticsText.setCharacterSize(10u);

	registerStates();
	mStateStack.pushState(States::Title);
}

void Application::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (mWindow.isOpen())
	{
		//Window Size Management - Now handled in ViewHandler
		/*if (mWindow.getSize().x*mScreenRatio.x != mWindow.getSize().y*mScreenRatio.y)
		{
			mWindow.setSize(sf::Vector2u(mWindow.getSize().x, mWindow.getSize().x/mScreenRatio.x*mScreenRatio.y)); 
		}*/

		sf::Time dt = clock.restart();
		timeSinceLastUpdate += dt;
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;

			processInput();
			update(TimePerFrame);

			// Check inside this loop, because stack might be empty before update() call
			if (mStateStack.isEmpty())
				mWindow.close();
		}

		updateStatistics(dt);
		render();
	}
}

void Application::processInput()
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		mStateStack.handleEvent(event);

		if (event.type == sf::Event::Closed)
			mWindow.close();
	}
}

void Application::update(sf::Time dt)
{
	Settings::updateFontSize(mWindow.getSize());
	mStateStack.update(dt);
}

void Application::render()
{
	mWindow.clear();

	mStateStack.draw();

	//mWindow.setView(mWindow.getDefaultView());
	//mWindow.draw(mStatisticsText);

	mWindow.display();
}

void Application::updateStatistics(sf::Time dt)
{
	mStatisticsUpdateTime += dt;
	mStatisticsNumFrames += 1;
	if (mStatisticsUpdateTime >= sf::seconds(1.0f))
	{
		mStatisticsText.setString("FPS: " + toString(mStatisticsNumFrames));

		mStatisticsUpdateTime -= sf::seconds(1.0f);
		mStatisticsNumFrames = 0;
	}
}

void Application::registerStates()
{
	mStateStack.registerState<TitleState>(States::Title);
	mStateStack.registerState<MenuState>(States::Menu);
	mStateStack.registerState<GameState>(States::Game);
	mStateStack.registerState<LoadingState>(States::Loading);
	mStateStack.registerState<PauseState>(States::Pause);
	mStateStack.registerState<SettingsState>(States::Settings);
	mStateStack.registerState<OverlayState>(States::Overlay);
}
