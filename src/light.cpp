#include "light.h"

#include <SFML/System.hpp>
#include "texture-manager.h"
#include "game.h"

Light::Light()
{
	//Register the light
	lights.push_back(this);

	sprite.setTexture(*TextureManager::getTexture("assets/light-big.png"));
	parentPositionOffset = sf::Vector2f(-192,-192);
	setLayer(SL_Lights);
	color = sf::Color(64,64,64,255);
}

Light::~Light()
{
	//Unregister
	for (int i = 0; i < lights.size(); i++)
		if (lights[i] == this) lights.erase(lights.begin()+i);
}

void Light::draw(sf::RenderTarget &target)
{
	//Temporary workaround for lighting renders to fix the viewport
	sf::Vector2f pos = static_cast<sf::Vector2f>(Game::instance()->window.mapCoordsToPixel(position));
	
	sprite.setPosition(pos);
	sprite.setColor(color);
	target.draw(sprite, sf::RenderStates(sf::BlendAdd));
}

std::vector<Light*> Light::lights;
