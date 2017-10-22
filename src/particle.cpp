#include "particle.h"

#include <stdlib.h>
#include "game.h"
#include "texture-manager.h"

//Get a random float centered on a range. Eg: range 50 -> [-25, 25]
float randomVariance(float range)
{
	float random = ((float) rand()) / (float) RAND_MAX;
	return range * random - (range / 2.0f);
}

//Random int from [-range/2, range/2]
int randomVariance(int range)
{
	if (range < 1) return 0;
	return rand() % range + 1 - (range / 2);
}

void Particle::randomize()
{
	velocity = initialVelocity;
	velocity.x += randomVariance(randomizeVelocity.x);
	velocity.y += randomVariance(randomizeVelocity.y);
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
