#include "tilemap.h"

TileMap::TileMap(	sf::Texture* texture, sf::Vector2i tileSize, 
					unsigned int tilesHigh, unsigned int tilesWide,
					int* map, unsigned int mapWidth, unsigned int mapHeight) :
					texture(texture), tileSize(tileSize),
					tilesHigh(tilesHigh), tilesWide(tilesWide),
					map(map), mapWidth(mapWidth), mapHeight(mapHeight)
{
	verticies.setPrimitiveType(sf::Quads);
	renderState.texture = texture;

	for (int i = 0; i < mapHeight; i++)
	{
		for (int j = 0; j < mapWidth; j++)
		{
			//The index of the tile texture, 0 would be top left tile
			int tile = map[mapHeight * i + j];

			//Each point on the quad to be rendered
			sf::Vertex point[4];
			point[0].position = sf::Vector2f(j * tileSize.x,		i * tileSize.y);		//top left
			point[1].position = sf::Vector2f((j + 1) * tileSize.x,	i * tileSize.y);		//top right
			point[2].position = sf::Vector2f((j + 1) * tileSize.x,	(i + 1) * tileSize.y);	//bottom right
			point[3].position = sf::Vector2f(j * tileSize.x,		(i + 1) * tileSize.x);	//bottom left

			//Get the current tile in the space of the tilemap texture, in pixels
			int mapX = tile % tilesWide * tileSize.x;
			int mapY = tile / tilesWide * tileSize.y;
			point[0].texCoords = sf::Vector2f(mapX,					mapY);
			point[1].texCoords = sf::Vector2f(mapX + tileSize.x,	mapY);
			point[2].texCoords = sf::Vector2f(mapX + tileSize.x,	mapY + tileSize.y);
			point[3].texCoords = sf::Vector2f(mapX,					mapY + tileSize.y);

			for (int k = 0; k < 4; k++)
			{
				verticies.append(point[k]);
			}
		}
	}
}

void TileMap::draw(sf::RenderTarget& target)
{
	//Update the transformation of the gameobject
	sf::Transform trans;
	trans.translate(position);
	trans.scale(scale);
	renderState.transform = trans;

	target.draw(verticies, renderState);
}
