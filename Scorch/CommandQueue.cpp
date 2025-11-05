
#include "CommandQueue.hpp"
#include "SceneNode.hpp"

void CommandQueue::push(const Command& command)
{
	mQueue.push(command);
}

void CommandQueue::push(const WorldCommand& command)
{
	mWQueue.push(command);
}

Command CommandQueue::pop()
{
	Command command = mQueue.front();
	mQueue.pop();
	return command;
}

WorldCommand CommandQueue::popWC()
{
	WorldCommand command = mWQueue.front();
	mWQueue.pop();
	return command;
}

bool CommandQueue::isEmpty() const
{
	return mQueue.empty();
}

bool CommandQueue::isWEmpty() const
{
	return mWQueue.empty();
}
