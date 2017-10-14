#include "particle.h"

#include "texture-manager.h"

void Particle::update(float deltaTime)
{
	if (!active) return;
	
	//Update physics
	velocity += deltaTime * acceleration;
	position += deltaTime * velocity;

	//Update lifetime
	lifetime += deltaTime;
	if (lifetime > lifespan) active = false;
}

void Particle::draw(sf::RenderTarget& target)
{
	if (!active) return;

	sprite.setPosition(position);
	color.a = 255 * (1.0 - lifetime/lifespan);
	sprite.setColor(color);
	target.draw(sprite, sf::RenderStates(sf::BlendAdd));
	//target.draw(sprite);
}
