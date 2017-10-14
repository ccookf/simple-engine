#ifndef PARTICLE_H
#define PARTICLE_H

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

class Particle
{
public:
	bool active {false};
	bool randomized {false};
	float lifespan {0};

	sf::Vector2f position {0, 0};
	sf::Vector2f velocity {0, 0};
	sf::Vector2f acceleration {0, 0};
	sf::Vector2f randomizeVelocity {0, 0}; //Variance

	sf::Sprite sprite;
	sf::Color color;

	Particle() {}
	~Particle() {}
	virtual void randomize();
	virtual void update();
	virtual void draw(sf::RenderTarget& target);

private:
	float lifetime {0};
};

#endif
