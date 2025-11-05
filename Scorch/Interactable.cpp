#include "Interactable.h"
#include "Categories.hpp"
#include <vector>

void Interactable::interact(Player_Entity& player) {

}

std::vector<unsigned int> Interactable::getCategory() const
{
	std::vector<unsigned int> i;
	i.push_back(Category::Interactable);
	return i;
}
