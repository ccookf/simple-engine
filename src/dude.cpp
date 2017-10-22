#include "dude.h"

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <vector>

#include "collision-layers.h"
#include "texture-manager.h"
#include "sprite-layers.h"
#include "vector-math.h"

Dude::Dude()
{
	setLayer(SL_Player);

	//Register actions to inputs
	game->input.assignCallbackToAction(Action_Down_Pressed, std::bind(&Dude::actionDownPressed, this));
	game->input.assignCallbackToAction(Action_Down_Released, std::bind(&Dude::actionDownReleased, this));
	game->input.assignCallbackToAction(Action_Up_Pressed, std::bind(&Dude::actionUpPressed, this));
	game->input.assignCallbackToAction(Action_Up_Released, std::bind(&Dude::actionUpReleased, this));
	game->input.assignCallbackToAction(Action_Left_Pressed, std::bind(&Dude::actionLeftPressed, this));
	game->input.assignCallbackToAction(Action_Left_Released, std::bind(&Dude::actionLeftReleased, this));
	game->input.assignCallbackToAction(Action_Right_Pressed, std::bind(&Dude::actionRightPressed, this));
	game->input.assignCallbackToAction(Action_Right_Released, std::bind(&Dude::actionRightReleased, this));

	game->input.assignCallbackToAction(Action_Special_Ability_1, std::bind(&Dude::actionSpecialAbility, this));

	//Idle animation
	idle.frames = {
		AnimationFrame(1, sf::IntRect(0,0,64,64))
	};
	idle.calculateMaxDuration();
	idle.setTexture(TextureManager::getTexture("assets/player.png"));
	idle.setOrigin(32, 32);
	idle.parent = this;
	idle.loop = true;

	//Walking animation
	walking.frames = {
		AnimationFrame(0.15, sf::IntRect(0,0,64,64)),
		AnimationFrame(0.15, sf::IntRect(64,0,128,64))
	};
	walking.calculateMaxDuration();
	walking.setTexture(TextureManager::getTexture("assets/player.png"));
	walking.setOrigin(32, 32);
	walking.parent = this;
	walking.loop = true;

	CollisionBoxManager* cbm = CollisionBoxManager::instance();
	cbm->add(CL_Physics, &hitbox);
	hitbox.parent = this;
	hitbox.setDimensions(64, 64);
	hitbox.setOrigin(32, 32);
	//hitbox.isVisible = true;
	hitbox.collisionMask = CL_Physics;

	cbm->add(CL_Physics, &sight);
	sight.parent = this;
	sight.setDimensions(250, 20);
	sight.setOrigin(32, 32);
	sight.setOffset(32, 18);
	//sight.isVisible = true;
	sight.color = sf::Color(255,255,0,128);

	//Setup the particle emission
	Particle sparkle;
	sparkle.lifespan = 1.0f;
	sparkle.sprite.setTexture(*TextureManager::getTexture("assets/light-small.png"));
	sparkle.sprite.setOrigin(16, 16);
	sparkle.color = sf::Color(200,200,200,255);
	sparkle.randomizeColor = sf::Color(55, 55, 55, 0);
	sparkle.acceleration = sf::Vector2f(0, 100);
	sparkle.randomized = true;
	sparkle.randomizeVelocity = sf::Vector2f(300, 300);
	sparkleEmitter = ParticleEmitter(sparkle, 0.1, this);
	sparkleEmitter.inheritVelocity = true;

	Particle trail;
	trail.lifespan = 2.0f;
	trail.sprite.setTexture(*TextureManager::getTexture("assets/light-small.png"));
	trail.sprite.setOrigin(16, 16);
	trail.color = sf::Color(255,255,255,255);
	trailEmitter = ParticleEmitter(trail, 0.025, this);
	trailEmitter.start();
}

Dude::~Dude()
{
	CollisionBoxManager* cbm = CollisionBoxManager::instance();
	cbm->remove(CL_Physics, &hitbox);
	cbm->remove(CL_Physics, &sight);
}

void Dude::update()
{
	if (!active) return;

	//This will cause the dude to face the direction of movement, 
	//but won't change direction if keys are released or
	//the player uses the opposite movement key to quick stop
	if (velocity.x < 0)
	{
		scale.x = abs(scale.x) * -1;
	}
	else if (velocity.x > 0)
	{
		
	scale.x = abs(scale.x);
	}

	physicsUpdate();
	hitbox.update();
	sight.update();
	sparkleEmitter.update();
	trailEmitter.update();

	//Determine and update the active animation
	if (mag(velocity) < 0.1) activeAnimation = &idle;
	else activeAnimation = &walking;

	if (!activeAnimation->playing) activeAnimation->play();
	activeAnimation->update();
}

void Dude::draw(sf::RenderTarget &target)
{
	if (!active) return;
	
	//update and draw sprite
	walking.sprite.setPosition(position);
	target.draw(walking.sprite);
	hitbox.draw(target);
	sight.draw(target);
}

void Dude::onCollision(CollisionBox* own, CollisionBox* other)
{
	//Collisions yo
}

/********************************************************************
 * ACTIONS
 *******************************************************************/

void Dude::actionUpPressed()
{
	velocity.y += -speed;
}

void Dude::actionUpReleased()
{
	velocity.y -= -speed;
}

void Dude::actionDownPressed()
{
	velocity.y += speed;
}

void Dude::actionDownReleased()
{
	velocity.y -= speed;
}

void Dude::actionLeftPressed()
{
	velocity.x -= speed;
}

void Dude::actionLeftReleased()
{
	velocity.x += speed;
}

void Dude::actionRightPressed()
{
	velocity.x += speed;
}

void Dude::actionRightReleased()
{
	velocity.x -= speed;
}

//The dude makes a boom!
void Dude::actionSpecialAbility()
{
	sparkleEmitter.burst(100);
}
