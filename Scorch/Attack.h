#pragma once

#include "SceneNode.hpp"
#include "Entity.hpp"
#include "Animation.h"
#include "Categories.hpp"

class Attack : public SceneNode
{
public:
	Attack();
	Attack(int damage, unsigned int category);
	Attack(int damage, unsigned int category, unsigned int animation);
	void dealDamage(Entity* target);

	virtual std::vector<unsigned int> getCategory() const;
	virtual unsigned int getTarget() const;
	virtual sf::FloatRect getBoundingRect() const;

	virtual Attack* clone() const = 0;

	virtual bool isDestroyed() const;
	virtual bool isFinnished();
	
	virtual sf::Time getCooldown();
	virtual sf::Time getDuration();
	virtual sf::Vector2f getOffset();

	virtual void flip();

	void setDirection(bool left, bool up);

	bool getDirectionX();
	bool getDirectionY();

	bool getIndependent();

	void setPairedAnimation(unsigned int animation);
	unsigned int getPairedAnimation();

	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void updateCurrent(sf::Time dt, CommandQueue& Commands);

protected:
	bool independent; //Attached to attacker or not

	int mDamage;
	sf::Vector2f mOffset;
	unsigned int mTarget;
	sf::Time mCooldown; //Time before you can attack again
	sf::Time mDuration; //Time attack lasts
	sf::Time mLifetime; //How long attack has existed
	std::vector<Entity*> mHit; //Ensures entities can only be hit once per attack
	bool left;
	bool up;
	unsigned int mPairedAnimation;
};

