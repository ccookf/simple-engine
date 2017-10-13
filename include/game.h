#ifndef GAME_H
#define GAME_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include "settings.h"

class Game
{
public:

	std::string title {"Game"};
	Settings settings;
	sf::RenderWindow& window;
	sf::RenderTexture lightBuffer;
	sf::Sprite lightBufferSprite;

	~Game();
	static Game* instance(sf::RenderWindow& window);

	void run();
	void resetWindow();

private:

	Game(sf::RenderWindow& window);
	static Game* _instance;
};

#endif
