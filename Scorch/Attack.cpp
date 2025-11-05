#include "Attack.h"
#include <iostream>

Attack::Attack()
: mDamage(0)
, mTarget(Category::Enemy)
, mCooldown(sf::seconds(0.5))
, mDuration(sf::seconds(0.5))
, mLifetime(sf::seconds(0))
, independent(false)
{
}

Attack::Attack(int damage, unsigned int category)
: mDamage(damage)
, mTarget(category)
, mCooldown(sf::seconds(0.5))
, mDuration(sf::seconds(0.5))
, mLifetime(sf::seconds(0))
, independent(false)
{

}

Attack::Attack(int damage, unsigned int category, unsigned int animation)
: mDamage(damage)
, mTarget(category)
, mCooldown(sf::seconds(0.5))
, mDuration(sf::seconds(0.5))
, mLifetime(sf::seconds(0))
, mPairedAnimation(animation)
, independent(false)
{

}

void Attack::dealDamage(Entity* target) 
{
	bool a = false;
	for (auto i : target->getCategory()) {
		if (mTarget == i) {
			a = true;
		}
	}
	if (a == false) {
		return;
	}
	for (Entity* i : mHit) {
		if (i == target) {
			return;
		}
	}
	if (!isFinnished()) {
		target->damage(mDamage);
	}
	mHit.push_back(target);
};

std::vector<unsigned int> Attack::getCategory() const{
	std::vector<unsigned int> i;
	i.push_back(Category::Attack);
	i.push_back(Category::Superlayer);
	return i;
}

unsigned int Attack::getTarget() const {
	return mTarget;
};

sf::FloatRect Attack::getBoundingRect() const {
	return sf::FloatRect();
};

bool Attack::isDestroyed() const {
	return mDuration <= mLifetime;
};

bool Attack::isFinnished() {
	return mDuration <= mLifetime;
}

sf::Time Attack::getCooldown()
{
	return mCooldown;
}

sf::Time Attack::getDuration()
{
	return mDuration;
}

sf::Vector2f Attack::getOffset()
{
	return mOffset;
}

void Attack::flip()
{
}

void Attack::setDirection(bool left, bool up)
{
	Attack::left = left;
	Attack::up = up;
	flip();
}

bool Attack::getDirectionX()
{
	return left;
}

bool Attack::getDirectionY()
{
	return up;
}

bool Attack::getIndependent()
{
	return independent;
}

void Attack::setPairedAnimation(unsigned int animation)
{
	mPairedAnimation = animation;
}

unsigned int Attack::getPairedAnimation()
{
	return mPairedAnimation;
}

void Attack::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {

};

void Attack::updateCurrent(sf::Time dt, CommandQueue& Commands) {
	mLifetime += dt;
};