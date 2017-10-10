#include <SFML/Graphics.hpp>
#include <string>
#include <map>

#include "texture-manager.h"

std::map<std::string, sf::Texture*> TextureManager::textures;

sf::Texture* TextureManager::getTexture(std::string filename)
{
	if (textures.find(filename) == textures.end())
	{
		sf::Texture* texture = new sf::Texture;
		texture->loadFromFile(filename);
		textures[filename] = texture;
		return texture;
	}
	else return textures[filename];
}

void TextureManager::unloadTexture(std::string filename)
{
	//Return if the texture doesn't exist already
	if (textures.find(filename) == textures.end()) return;
	
	sf::Texture* texture = textures[filename];
	delete texture;
}
