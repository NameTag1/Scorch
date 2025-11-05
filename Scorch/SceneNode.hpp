#ifndef Scenenode_hpp
#define Scenenode_hpp

#include "Categories.hpp"
#include "CommandQueue.hpp"

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>

#include <vector>
#include <memory>
#include <set>


struct Command;
class CommandQueue;

class SceneNode : public sf::Transformable, public sf::Drawable
{
	public:
		typedef std::unique_ptr<SceneNode> Ptr;
		typedef std::pair<SceneNode*, SceneNode*> Pair;


	public:
								SceneNode();

		void					attachChild(Ptr child);
		Ptr						detachChild(const SceneNode& node);
		void					clearChildren();
		
		void					update(sf::Time dt, CommandQueue& commands);
		void					drawSolo(sf::RenderTarget& target); //Built for "violating" the heriarchial rendering order

		sf::Vector2f			getWorldPosition() const;
		sf::Transform			getWorldTransform() const;

		void					onCommand(const Command& command, sf::Time dt);
		virtual std::vector<unsigned int> getCategory() const;

		void					checkSceneCollision(SceneNode& sceneGraph, std::set<Pair>& collisionPairs);
		void					checkNodeCollision(SceneNode& node, std::set<Pair>& collisionPairs);
		void					findCategory(std::vector<SceneNode*>& categoryMembers, Category::Type c);

		virtual sf::FloatRect	getBoundingRect() const;

		void					removeWrecks();
		virtual bool			isMarkedForRemoval() const;
		virtual bool			isDestroyed() const;

	private:
		virtual void			updateCurrent(sf::Time dt, CommandQueue& commands);
		void					updateChildren(sf::Time dt, CommandQueue& commands);

		virtual void			draw(sf::RenderTarget& target, sf::RenderStates states) const;
		virtual void			drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
		void					drawChildren(sf::RenderTarget& target, sf::RenderStates states) const;

		bool					collision(const SceneNode& lhs, const SceneNode& rhs);
		float					distance(const SceneNode& lhs, const SceneNode& rhs);

	private:
		std::vector<Ptr>		mChildren;
		SceneNode*				mParent;
};

#endif 
