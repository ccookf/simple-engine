#ifndef DUDE_H
#define DUDE_H

#include "animation.h"
#include "audio.h"
#include "collision-box.h"
#include "gameobject.h"
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

	ParticleEmitter sparkleEmitter;
	ParticleEmitter trailEmitter;

	CollisionBox hitbox;
	CollisionBox sight;

	Audio* audio {Audio::instance()};

	Dude();
	~Dude();
	void update();
	void draw(sf::RenderTarget &target);
	void onCollision(CollisionBox* own, CollisionBox* other);

	//Input actions
	void actionUpPressed();
	void actionUpReleased();
	void actionDownPressed();
	void actionDownReleased();
	void actionLeftPressed();
	void actionLeftReleased();
	void actionRightPressed();
	void actionRightReleased();
	void actionSpecialAbility();
};

#endif
