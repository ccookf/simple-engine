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

void ParticleManager::updateAndDraw(float deltaTime, sf::RenderTarget& target)
{
	#ifdef DEBUG
	int active = 0;
	#endif
	
	for (Particle* ptr = particles; ptr < particles + MAX_PARTICLE_COUNT; ++ptr)
	{
		ptr->update(deltaTime);
		ptr->draw(target);
		
		#ifdef DEBUG
		if (ptr->active) active++;
		#endif
	}

	#ifdef DEBUG
	activeParticles = active;
	#endif
}
