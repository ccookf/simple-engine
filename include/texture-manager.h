#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

// @todo - Figure out how I want to handle texture unloading for scenes
class TextureManager
{
public:
	static sf::Texture* getTexture(std::string filename);
	static void unloadTexture(std::string filename);

private:
	static std::map<std::string, sf::Texture*> textures;
};

#endif
