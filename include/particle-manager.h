#ifndef PARTICLE_MANAGER_H
#define PARTICLE_MANAGER_H

#define MAX_PARTICLES 500

#include <SFML/Graphics.hpp>
#include "particle.h"

class ParticleManager
{
public:
	Particle* getFreeParticle();
	void updateAndDraw(float deltaTime, sf::RenderTarget& target);

	static ParticleManager* instance();

private:
	static ParticleManager* _instance;
	int activeParticles {0};
	const int MAX_PARTICLE_COUNT {MAX_PARTICLES};
	Particle particles[MAX_PARTICLES];
	ParticleManager() {}
};

#endif
