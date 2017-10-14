#include "particle-manager.h"

#ifdef DEBUG
#include <iostream>
#endif

//Singleton
ParticleManager* ParticleManager::_instance;
ParticleManager* ParticleManager::instance()
{
	if (_instance == nullptr) _instance = new ParticleManager();
	return _instance;
}

// @todo test if storing free particles in a queue is faster
// Oct 14, 2017 - I tried with queues and vectors, no benefit. draw() is the problem
Particle* ParticleManager::getFreeParticle()
{
	for (Particle* ptr = particles; ptr < particles + MAX_PARTICLE_COUNT; ++ptr)
	{
		if (ptr->active == false) return ptr;
	}

	#ifdef DEBUG
	std::cout << "ERROR: getFreeParticle() found no inactive particles!" << std::endl;
	#endif

	return nullptr;
}

// @todo - Desperately need to implement a batching solution
void ParticleManager::updateAndDraw(sf::RenderTarget& target)
{
	#ifdef DEBUG
	int active = 0;
	#endif
	
	for (Particle* ptr = particles; ptr < particles + MAX_PARTICLE_COUNT; ++ptr)
	{
		ptr->update();
		ptr->draw(target);
		
		#ifdef DEBUG
		if (ptr->active) active++;
		#endif
	}

	#ifdef DEBUG
	activeParticles = active;
	#endif
}
