#ifndef TILEMAP_H
#define TILEMAP_H

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "gameobject.h"

// @notes - Most gameobject utilities will be relevant for advanced backgrounds
class TileMap : public GameObject
{
public:

	TileMap() {}
	TileMap(	sf::Texture* texture, sf::Vector2i tileSize, 
				unsigned int tilesHigh, unsigned int tilesWide,
				int* map, unsigned int mapWidth, unsigned int mapHeight);
	void draw(sf::RenderTarget& target);

private:
	//Texture details
	sf::Texture* texture;
	sf::Vector2i tileSize;
	unsigned int tilesHigh;
	unsigned int tilesWide;

	//Map
	int* map;
	unsigned int mapWidth;
	unsigned int mapHeight;

	//Rendering variables
	sf::VertexArray verticies;
	sf::RenderStates renderState;
};

#endif
