#pragma once

#include "Categories.hpp"

#include <SFML/System.hpp>

#include <functional>
#include <cassert>


class World;

struct WorldCommand
{
	WorldCommand();

	std::function<void(World&)>	action;
};

template <typename GameObject, typename Function>
std::function<void(World&)> derivedWorldAction(Function fn)
{
	return [=](World& world)
		{
			// Check if cast is safe
			assert(dynamic_cast<GameObject*>(&world) != nullptr);

			// Downcast node and invoke function on it
			fn(static_cast<GameObject&>(world));
		};
}


