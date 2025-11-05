#ifndef Book_Command_Queue_hpp
#define Book_Command_Queue_hpp

#include "Command.hpp"
#include "WorldCommand.h"

#include <queue>


class CommandQueue
{
	public:
		void push(const Command& command);
		void push(const WorldCommand& worldCommand);
		Command pop();
		WorldCommand popWC();
		bool isEmpty() const;
		bool isWEmpty() const;

		
	private:
		std::queue<Command>			mQueue;
		std::queue<WorldCommand>	mWQueue;
};

#endif
