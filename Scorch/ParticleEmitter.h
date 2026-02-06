#pragma once

#include "SceneNode.hpp"
#include "Particle.h"
#include "DataTable.h"

#include "nlohmann/json.hpp"
using json = nlohmann::json;

class ParticleEmitter : public SceneNode
{
public:
	ParticleEmitter(TextureHolder& textureHolder, json data, bool SuperLayer);
	virtual std::vector<unsigned int> getCategory() const;

private:
	virtual void			updateCurrent(sf::Time dt, CommandQueue& commands);
	virtual void			draw(sf::RenderTarget& target, sf::RenderStates states) const;

	std::deque<Particle>	mParticles;

	sf::VertexArray mParticle;
	sf::Texture& mParticleTexture;

	bool mSuperLayer;
};

