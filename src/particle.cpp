#include "particle.h"

#include <stdlib.h>
#include "texture-manager.h"

void Particle::randomize()
{
	float random = ((float) rand()) / (float) RAND_MAX;
	velocity.x = randomizeVelocity.x * random - (randomizeVelocity.x / 2.0f);

	random = ((float) rand()) / (float) RAND_MAX;
	velocity.y = randomizeVelocity.x * random - (randomizeVelocity.x / 2.0f);	
}

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
}
