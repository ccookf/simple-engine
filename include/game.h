#ifndef GAME_H
#define GAME_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include "settings.h"

class Camera;
class Scene;

class Game
{
public:

	//Game settings
	std::string title {"Game"};
	Settings settings;

	Scene* activeScene {nullptr};

	//Runtime variables
	static float deltaTime;

	//Rendering
	Camera* camera {nullptr};
	sf::RenderTexture lightBuffer;
	sf::Sprite lightBufferSprite;
	sf::RenderWindow& window;

	~Game();
	static Game* create(sf::RenderWindow& window);
	static Game* instance();

	void loadScene(Scene* scene);
	void run();
	void resetWindow();

private:

	Game(sf::RenderWindow& window);
	static Game* _instance;
};

#endif
