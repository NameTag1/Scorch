#include "Enemy.h"
#include "MoveDis.h"
#include "Jump.h"
#include "Pause.h"
#include "Slash.h"
#include "ChasePlayer.h"
#include "FleePlayer.h"
#include "MakeAttack.h"
#include "Utility.hpp"
#include "With.h"

Enemy::Enemy(const TextureHolder& resources)
: Platformer(50)
, isMarkedForRemoval(false)
, isAttacking(false)
, mSprite(resources.get(Textures::Enemy))
{
	centerOrigin(mSprite);
	setSpeed(70);
	Actionable::pushAction(new Jump());
	Actionable::pushAction(new ChasePlayer(200));
	Actionable::pushAction(new Pause(sf::seconds(1)));
	Actionable::pushAction(new MakeAttack("Slash"));
	Actionable::pushAction(new Pause(sf::seconds(1)));
	Actionable::pushAction(new FleePlayer(500));
	Actionable::pushAction(new Pause(sf::seconds(1)));
	
	Attacker::pushAttack("Slash", new Slash(500, (unsigned int)Category::Player, resources));
	/*Actionable::pushAction(*new Move(-500));
	Actionable::pushAction(*new Jump());
	Actionable::pushAction(*new Move(250));*/
}

std::vector<unsigned int> Enemy::getCategory() const {
	std::vector<unsigned int> i(Platformer::getCategory());
	i.push_back(Category::Enemy);
	return i;
};

sf::FloatRect Enemy::getBoundingRect() const {
	return getWorldTransform().transformRect(mSprite.getGlobalBounds());
};

bool Enemy::markedForRemoval() {
	return isMarkedForRemoval;
};

void Enemy::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(mSprite, states);
};

void Enemy::updateCurrent(sf::Time dt, CommandQueue& Commands) {
	if (Entity::isDestroyed()) {
		isMarkedForRemoval = true;
		return;
	}

	Attacker::update(dt, Commands, *this);

	Actionable::update(dt, Commands, *this);

	Platformer::updateCurrent(dt, Commands);
};