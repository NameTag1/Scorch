#include "LoadingState.h"
#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.hpp"
#include "DataTable.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>


#include <thread>
#include <iostream>

#include <string>


LoadingState::LoadingState(StateStack& stack, Context context)
	: State(stack, context)
	, loadingText("Loading", context.fonts->get(Fonts::Main))
	, mTimer()
	, loadingDuration(sf::seconds(0.5))
	, builder(Scene_Builder::getInstance())
	, world(World::getInstance())
	, mThread(&LoadingState::BeginLoading, this)
	, mThreadDone(false)
{
}

LoadingState::~LoadingState()
{
}

void LoadingState::BeginLoading()
{
	mThreadDone = false;
	DATATABLE::prepareJsonFile();
	DATATABLE::prepareData();
	//builder->buildScene(world->requestSceneChange().scene, world->requestSceneChange().playerPos);
	//world->prepareSceneForPlay(builder);
	sf::Clock i;
	//while (i.getElapsedTime() < sf::seconds(5)) {

	//}

	mThreadDone = true;
}

void LoadingState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	window.setView(window.getDefaultView());

	sf::RectangleShape backgroundShape;
	backgroundShape.setFillColor(sf::Color(50, 50, 50, 150));
	backgroundShape.setSize(window.getView().getSize());

	window.draw(loadingText);
}

bool LoadingState::update(sf::Time dt)
{
	if (mTimer.getElapsedTime() >= loadingDuration) {
		std::string s = loadingText.getString();
		if (s.length() >= 10) {
			s.erase(7, 3);
		}
		else {
			s.append(".");
		}
		loadingText.setString(s);
		mTimer.restart();
	};

	if (mThread.joinable() && mThreadDone) {
		mThread.join();
		requestStackPop();
		mThreadDone = false;
	}
	return false;
}

bool LoadingState::handleEvent(const sf::Event& event)
{
	return false;
}