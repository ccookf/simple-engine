#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "light.h"

Light::Light()
{
	//Register the light
	lights.push_back(this);

	sprite.setTexture(*TextureManager::getTexture("assets/light-big.png"));
	parentPositionOffset = sf::Vector2f(-192,-192);
	layer = SpriteLayer::Lights;
	color = sf::Color(255,128,128,255);
}

Light::~Light()
{
	//Unregister
	for (int i = 0; i < lights.size(); i++)
		if (lights[i] == this) lights.erase(lights.begin()+i);
}

void Light::Draw(sf::RenderTarget &target)
{
	sprite.setPosition(position);
	sprite.setColor(color);
	target.draw(sprite);
}

std::vector<Light*> Light::lights;