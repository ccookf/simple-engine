/**
 * Game core
 * 
 * Preprocessor flags "g++ -D flag(=value)":
 *  DEBUG
 */

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "game.h"

int main()
{
	sf::RenderWindow window;
	Game* game = Game::instance(window);
	game->run();

	return 0;
}
