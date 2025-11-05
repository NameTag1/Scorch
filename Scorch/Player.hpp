#pragma once

#ifndef Player_hpp
#define Player_hpp


#include "Command.hpp"

#include <SFML/Window/Event.hpp>

#include <map>


class CommandQueue;

class Player
{
	public:
		enum PActions
		{
			MoveLeft,
			MoveRight,
			MoveDown,
			JumpA,
			InteractA,
			Attack1,
			Attack2,
			Attack3,
			Attack4,
			ActionCount
		};


	public:
								Player();

		void					handleEvent(const sf::Event& event, CommandQueue& commands);
		void					handleRealtimeInput(CommandQueue& commands);

		void					assignKey(PActions action, sf::Keyboard::Key key);
		sf::Keyboard::Key		getAssignedKey(PActions action) const;

	private:
		void					initializeActions();
		static bool				isRealtimeAction(PActions action);


	private:
		std::map<sf::Keyboard::Key, PActions>		mKeyBinding;
		std::map<PActions, Command>				mActionBinding;
};

#endif 
