#include "particle-emitter.h"

#include "gameobject.h"
#include "particle-manager.h"

#include <cmath> //fmod(float)

ParticleEmitter::ParticleEmitter()
{
	particleManager = ParticleManager::instance();
}

ParticleEmitter::ParticleEmitter(Particle particle, float rate, GameObject* parent) : 
	particle(particle), rate(rate), parent(parent) 
{
	particleManager = ParticleManager::instance();
}

void ParticleEmitter::start()
{
	elapsed = 0;
	active = true;
}

void ParticleEmitter::stop()
{
	active = false;
}

void ParticleEmitter::burst(int count)
{
	//Prepare the particle to be emitted
	particle.position = parent->position + parentPositionOffset;

	for (int i = 0; i < count; i++)
	{
		if (particle.randomized) particle.randomize();
		if (inheritVelocity) particle.velocity += parent->velocity;

		Particle* pt = particleManager->getFreeParticle();
		if (pt == nullptr) return;
		*pt = particle;
	}
}

void ParticleEmitter::update()
{
	if (!active | parent == nullptr) return;
	if (rate <= 0) return;

	elapsed += Game::deltaTime;
	if (elapsed < rate) return;
	else
	{		
		//If get the number of particles to emit, 
		//useful if the rate of emission exceeds the framerate
		int emissionCount = static_cast<int>(elapsed / rate);

		//Prepare the particle to be emitted
		particle.position = parent->position + parentPositionOffset;
	
		for (int i = 0; i < emissionCount; i++)
		{
			if (particle.randomized) particle.randomize();
			if (inheritVelocity) particle.velocity += parent->velocity;
	
			Particle* pt = particleManager->getFreeParticle();
			if (pt == nullptr) return;
			*pt = particle;
		}

		//Reset the time to emission without truncating
		elapsed = fmod(elapsed, rate);
	}
}
