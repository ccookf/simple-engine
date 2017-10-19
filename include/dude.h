#ifndef DUDE_H
#define DUDE_H

#include "gameobject.h"
#include "animation.h"
#include "collision-box.h"
#include "particle.h"
#include "particle-emitter.h"

enum class PlayerState
{
	Idle,
	Walking
};

class Dude : public GameObject
{
public:
	float speed { 300 };

	PlayerState state { PlayerState::Idle };
	bool isFacingRight { true };
	Animation* activeAnimation { &idle };
	Animation idle;
	Animation walking;

	Particle sparkle;
	ParticleEmitter sparkleEmitter;

	CollisionBox hitbox;
	CollisionBox sight;

	Dude();
	~Dude();
	void update();
	void draw(sf::RenderTarget &target);
	void onCollision(CollisionBox* own, CollisionBox* other);
};

#endif
