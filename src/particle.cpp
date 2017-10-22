#include "particle.h"

#include <stdlib.h>
#include "game.h"
#include "texture-manager.h"
#include "util.h"
#include "vector-math.h"

void Particle::randomize()
{
	velocity = initialVelocity;
	velocity.x += randomVariance(randomizeVelocity.x);
	velocity.y += randomVariance(randomizeVelocity.y);
	if (circular)
	{
		velocity = (speed + randomVariance(randomizeSpeed)) * normalize(velocity);
	}

	color.r = randomVariance(randomizeColor.r);
	color.g = randomVariance(randomizeColor.g);
	color.b = randomVariance(randomizeColor.b);
	color.a = randomVariance(randomizeColor.a);
}

void Particle::update()
{
	if (!active) return;
	
	//Update physics
	float deltaTime = Game::deltaTime;
	velocity += deltaTime * acceleration;
	position += deltaTime * velocity;

	//Update lifetime
	lifetime += deltaTime;
	if (lifetime > lifespan) active = false;
}

void Particle::draw(sf::RenderTarget& target)
{
	if (!active) return;

	//Temporary workaround for lighting renders to fix the viewport
	sf::Vector2f pos = static_cast<sf::Vector2f>(Game::instance()->window.mapCoordsToPixel(position));

	sprite.setPosition(pos);
	color.a = 255 * (1.0 - lifetime/lifespan);
	sprite.setColor(color);
	target.draw(sprite, sf::RenderStates(sf::BlendAdd));
}
