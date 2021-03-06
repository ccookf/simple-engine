#ifndef PARTICLE_MANAGER_H
#define PARTICLE_MANAGER_H

// @todo move this macro to engine variable
#define MAX_PARTICLES 3000

#include "particle.h"
#include "game.h"

class ParticleManager
{
public:
	Particle* getFreeParticle();
	void updateAndDraw(sf::RenderTarget& target);
	void freeAllParticles();

	static ParticleManager* instance();

private:
	static ParticleManager* _instance;
	Game* game {Game::instance()};
	const int MAX_PARTICLE_COUNT {MAX_PARTICLES};
	Particle particles[MAX_PARTICLES];
	ParticleManager() {}

	#ifdef DEBUG
	int activeParticles {0};
	#endif
};

#endif
