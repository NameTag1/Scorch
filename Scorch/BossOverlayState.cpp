#include "BossOverlayState.h"
#include <unordered_set>

BossOverlayState* BossOverlayState::mInstance = nullptr;

BossOverlayState::BossOverlayState(StateStack& stack, Context context)
: State(stack, context)
{
	mInstance = this;
	mGUIContainer.setRelativeRect(RelativeRect(sf::FloatRect(0, 0, 0.65f, 0.10f), RelativeWH::WHBased, Anchor::Center));
}

BossOverlayState* BossOverlayState::getInstance(StateStack& stack, Context context)
{
    return mInstance;
}

void BossOverlayState::addBoss(Entity* boss)
{
	mBossHealthbars[boss] = new GUI::Bar();
}

void BossOverlayState::draw()
{
    sf::RenderWindow& window = *getContext().window;
    sf::View mView(sf::FloatRect(0, 0, float(window.getSize().x), float(window.getSize().y)));
    window.setView(mView);

    window.draw(mGUIContainer);
};

bool BossOverlayState::update(sf::Time dt)
{
	int numberOfBosses = int(mBossHealthbars.size());
	int i = 0;
    for (const auto& [entity, bar] : mBossHealthbars) {
        //Boss destroyed, remove it from the vector
        if (!entity || entity->isDestroyed()) {
            std::erase_if(mBossHealthbars, [entity](const auto& pair) {
                if (pair.first == entity) {
                    delete pair.second; // Clean up the GUI::Bar memory if this vector owns it!
                    return true;
                }
                return false;
                });

            delete entity;             // 1. Free memory (if owned by this vector)
        }
        else {
            // Fit bars inside the container, dividing full width by the number of bosses
            RelativeRect barRect(sf::FloatRect(0.f + i * 1.f / numberOfBosses, 0.f, 1.f / numberOfBosses, 1.f), RelativeWH::Normal, Anchor::TL);
            i++;

            bar->setMessure(float(entity->getMaxHitpoints()), float(entity->getHitpoints())); // Update the health bar with the boss's current health
            //bar->setRelativeRect(barRect);
            bar->updateRect(mGUIContainer.getRect());
        }
    }

	return true;
}

bool BossOverlayState::handleEvent(const sf::Event& event)
{

};


