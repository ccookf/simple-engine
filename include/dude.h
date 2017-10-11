#ifndef DUDE_H
#define DUDE_H

#include "gameobject.h"
#include "animation.h"
#include "collision-box.h"

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

	CollisionBox hitbox;
	CollisionBox sight;

	Dude();
	void Update(float deltaTime);
	void Draw(sf::RenderTarget &target);
	void OnCollision(CollisionBox* own, CollisionBox* other);
};

#endif