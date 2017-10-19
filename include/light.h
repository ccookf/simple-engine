#ifndef LIGHT_H
#define LIGHT_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "gameobject.h"

class Light : public GameObject
{
public:
	sf::Sprite sprite;
	sf::Color color;

	Light();
	~Light();

	void draw(sf::RenderTarget &target);

	static std::vector<Light*> lights;
};

#endif
