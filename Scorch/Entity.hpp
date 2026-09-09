#ifndef Entity_hpp
#define Entity_hpp


#include "SceneNode.hpp"
#include <cassert>
#include "CommandQueue.hpp"
#include "Movable.h"

class Entity
{
	public:
		explicit			Entity(int hitpoints);

		virtual std::vector<unsigned int> getCategory() const;

		int					getHitpoints();
		int					getMaxHitpoints();
		void				heal(int heal);
		void				damage(int damage);
		virtual bool		isDestroyed() const;

	private:
		int					mMaxHitpoints;
		int					mHitpoints;
};

#endif // BOOK_ENTITY_HPP
