#ifndef PARTICLE_H
#define PARTICLE_H

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

class Particle
{
public:
	bool active {true};
	bool randomized {false};
	bool circular {false};
	float lifespan {0};

	//Use these for constant factors
	sf::Vector2f position {0, 0};
	sf::Vector2f velocity {0, 0};
	sf::Vector2f acceleration {0, 0};

	//Use initial when randomizing
	sf::Vector2f initialVelocity {0, 0};
	sf::Vector2f randomizeVelocity {0, 0}; //Variance
	sf::Color randomizeColor {0, 0, 0, 0}; //Variance of each channel

	/**
	 * For circular randomization.
	 * 
	 * This works by normalizing the randomized velocity from above, then 
	 * scaling by speed, which gives a ring effect. The speed can also be
	 * randomized, giving a fireworks like effect.
	 **/
	float speed {0};
	float randomizeSpeed {0};

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
