#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

class TextureManager
{
public:
	static sf::Texture* getTexture(std::string filename);
	static void unloadTexture(std::string filename);

private:
	static std::map<std::string, sf::Texture*> textures;
};

#endif
