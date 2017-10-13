/**
 * Game core
 * 
 * Preprocessor flags "g++ -D flag(=value)":
 *  DEBUG
 */

#include "game.h"

int main()
{
	Game* game = Game::instance();
	game->run();

	return 0;
}
