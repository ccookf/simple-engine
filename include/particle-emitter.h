#ifndef PARTICLE_EMITTER_H
#define PARTICLE_EMITTER_H

#include <SFML/System.hpp>
#include "particle.h"
#include "particle-manager.h"
#include "game.h"
#include "gameobject.h"

class ParticleEmitter
{
public:
	bool active {false};
	Particle particle;
	GameObject* parent {nullptr};
	sf::Vector2f parentPositionOffset {0,0};

	float rate {0};			//Interval between emissions

	//Constructors
	ParticleEmitter() 
	{
		particleManager = ParticleManager::instance();
	}
	ParticleEmitter(Particle particle, float rate, GameObject* parent) : 
		particle(particle), rate(rate), parent(parent) 
	{
		particleManager = ParticleManager::instance();
	}

	//Methods
	virtual void start();
	virtual void stop();
	virtual void update();

private:
	ParticleManager* particleManager {nullptr};
	float elapsed {0};		//Time since last emission
};

#endif
