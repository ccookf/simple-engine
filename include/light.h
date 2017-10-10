#ifndef LIGHT_H
#define LIGHT_H

#include "gameobject.h"
#include "texture-manager.h"

class Light : public GameObject
{
public:
	sf::Sprite sprite;
	sf::Color color;

	Light();
	~Light();

	void Draw(sf::RenderTarget &target);

	static std::vector<Light*> lights;
};

#endif
