#include "ParticleEmitter.h"
#include "Utility.hpp"

ParticleEmitter::ParticleEmitter(TextureHolder& textureHolder, json data, bool SuperLayer)
	: mParticleTexture(textureHolder.get(std::string(data["Texture"])))
	, mSuperLayer(SuperLayer)
{
}

std::vector<unsigned int> ParticleEmitter::getCategory() const
{
	if(mSuperLayer)
		return std::vector<unsigned int>(1, Category::Superlayer);
	return std::vector<unsigned int>();
}

void ParticleEmitter::updateCurrent(sf::Time dt, CommandQueue& commands)
{
	for (auto& i : mParticles) {
		i.mLifetime -= dt;
	}

	while (!mParticles.empty() && mParticles.front().mLifetime <= sf::Time::Zero)
	{
		mParticles.pop_front();
	}
}

void ParticleEmitter::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.texture = &mParticleTexture;

	//target.draw(, states);
}
