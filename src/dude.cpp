#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <vector>

#include "texture-manager.h"
#include "vector-math.h"
#include "collision-layers.h"
#include "sprite-layers.h"

#include "dude.h"

Dude::Dude()
{
	setLayer(SpriteLayer::Player);

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
}

void Dude::Update(float deltaTime)
{
	if (!active) return; 

	velocity = sf::Vector2f(0, 0);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		velocity.y = -speed;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		velocity.y = speed;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		velocity.x = -speed;
		scale.x = abs(scale.x) * -1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		velocity.x = speed;
		scale.x = abs(scale.x);
	}
	PhysicsUpdate(deltaTime);
	hitbox.Update();
	sight.Update();

	//Determine and update the active animation
	if (mag(velocity) < 0.1) activeAnimation = &idle;
	else activeAnimation = &walking;

	if (!activeAnimation->playing) activeAnimation->play();
	activeAnimation->Update(deltaTime);
}

void Dude::Draw(sf::RenderTarget &target)
{
	if (!active) return;
	
	//update and draw sprite
	walking.sprite.setPosition(position);
	target.draw(walking.sprite);
	hitbox.Draw(target);
	sight.Draw(target);
}

void Dude::OnCollision(CollisionBox* own, CollisionBox* other)
{
	//Collisions yo
}
