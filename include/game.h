#ifndef GAME_H
#define GAME_H

class Game
{
public:

	~Game();
	static Game* instance();

	void run();

private:

	Game();
	static Game* _instance;
};

#endif
