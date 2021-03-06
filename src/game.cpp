#include "game.h"

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>

#include "audio.h"
#include "camera.h"
#include "collision-box.h"
#include "collision-layers.h"
#include "fps-counter.h"
#include "gameobject.h"
#include "particle-manager.h"
#include "scene.h"

#include "demo-scene.h"

//Static variables
Game* Game::_instance;
float Game::deltaTime;

//Constructors
Game::Game(sf::RenderWindow& window) : window(window) 
{
	camera = new Camera();
}
Game::~Game() 
{
	delete camera;
}
Game* Game::create(sf::RenderWindow& window)
{
	if (_instance == nullptr) _instance = new Game(window);
	return _instance;
}
Game* Game::instance() { return _instance; }

//Unloads and replaces the active scene, which is then reloaded
// @notes - it may be beneficial to keep and return the old scene
//			to allow for maintaining scene state for backtracking
//			eg. entities maintain position rather than resetting
void Game::loadScene(Scene* scene = nullptr)
{
	if (scene == nullptr)
	{
		std::cout << "Error, Game::loadScene() received nullptr\n";
		return;
	}
	if (activeScene != nullptr) 
	{
		std::cout << "Unloading scene: " << activeScene->name << std::endl;
		activeScene->unload();
		ParticleManager::instance()->freeAllParticles();
	}
	activeScene = scene;
	std::cout << "Active Scene: " << activeScene->name << std::endl;
	activeScene->load();
}

//Game loop
void Game::run()
{
	srand(time(NULL));
	
	#ifdef DEBUG
	std::cout << "Launching debug build...\n";
	#endif
	
	//Recreate window from stored settings
	resetWindow();

	//Load the initial scene
	loadScene(new DemoScene());

	//Engine maintenance
	SpriteLayerManager* spriteLayerManager = SpriteLayerManager::instance();
	CollisionBoxManager* collisionBoxManager = CollisionBoxManager::instance();
	ParticleManager* particleManager = ParticleManager::instance();
	Audio* audio = Audio::instance();
	std::vector<GameObject*> &gameObjects = GameObject::gameObjects;
	sf::Clock clock;
	FpsCounter fps;

	//SFML window event loop
	// @todo replace manual input with command mapping later
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				switch (event.key.code)
				{
					case (sf::Keyboard::Escape):
						window.close();
						break;

					case (sf::Keyboard::F1):

						settings.resolution.x = 1600;
						settings.resolution.y = 900;
						settings.fullscreen = false;
						resetWindow();
						break;

					case (sf::Keyboard::F2):

						settings.resolution.x = 800;
						settings.resolution.y = 600;
						settings.fullscreen = false;
						resetWindow();
						break;

					case (sf::Keyboard::Dash):

						settings.lightLevel -= 0.01;
						settings.lightLevel = settings.lightLevel < 0.0 ? 0.0 : settings.lightLevel;
						break;

					case (sf::Keyboard::Equal):

						settings.lightLevel += 0.01;
						settings.lightLevel = settings.lightLevel > 1.0 ? 1.0 : settings.lightLevel;
						break;

					case (sf::Keyboard::K):
						activeScene->unload();
						break;

					case (sf::Keyboard::L):
						loadScene(new DemoScene());
						break;

					default:
						input.processPressed(event.key.code);
				}
			}
			else if (sf::Event::KeyReleased)
			{
				input.processReleased(event.key.code);
			}
		}

		//Update all GameObjects
		deltaTime = clock.restart().asSeconds();
		for (int i = 0; i < gameObjects.size(); i++)
			gameObjects[i]->update();

		//Cull unused sounds
		audio->update();

		//Check for collisions
		for (auto layer : RegisteredCollisionLayers)
		{
			//For every box in every layer
			for (auto box : collisionBoxManager->map[layer])
			{
				//Skip boxes without parents or inactive gameobjects
				if (box->parent == nullptr || !box->parent->active) continue;

				//Check the box against other boxes
				for (auto otherLayer : RegisteredCollisionLayers)
				{
					//Check if the box can interact with the other layer
					if (box->collisionMask & otherLayer)
					{
						for (auto otherBox : collisionBoxManager->map[otherLayer])
						{
							box->checkCollision(otherBox);
						}
					}
				}
			}
		}

		//Clear the render textures for drawing
		window.clear(sf::Color::Black);
		int bc = settings.lightLevel * 255; //set the light level
		lightBuffer.clear(sf::Color(bc, bc, bc, 255));

		//Update the camera & light buffer to set the render region
		camera->update();
		lightBufferSprite.setPosition(window.mapPixelToCoords(sf::Vector2i(0, 0)));

		//Drawing all objects, ordered by layer
		for (auto layer : RegisteredSpriteLayers)
		{
			if (layer == SL_Lights)
			{
				//Draw all lights to the light buffer
				for (auto obj : spriteLayerManager->map[layer])
				{
					if (obj->active) obj->draw(lightBuffer);
				}
			}
			else
			{
				//Draw to back buffer
				for (auto obj : spriteLayerManager->map[layer])
				{
					if (obj->active) obj->draw(window);
				}
			}
		}

		//Update and draw all particles
		particleManager->updateAndDraw(lightBuffer);

		//Multiply the light map onto the window
		window.draw(lightBufferSprite, sf::RenderStates(sf::BlendMultiply));
		
		//Update the fps counter
		fps.update(deltaTime);
		fps.text.setPosition(window.mapPixelToCoords(sf::Vector2i(0,0)));
		window.draw(fps.text);

		//End game loop and display new frame
		window.display();
	}
}

void Game::resetWindow()
{
	int style = settings.fullscreen ? sf::Style::Fullscreen : sf::Style::Close;

	//Setup the light buffer
	lightBuffer.create(settings.resolution.x, settings.resolution.y);
	lightBufferSprite.setTexture(lightBuffer.getTexture());
	lightBufferSprite.setTextureRect
	(
		sf::IntRect
		(
			0, 
			settings.resolution.y,
			settings.resolution.x,
			-settings.resolution.y
		)
	);

	window.create
	(
		sf::VideoMode(settings.resolution.x, settings.resolution.y),
		title,
		style
	);

	if (settings.fpsCapped) window.setFramerateLimit(settings.fpsCap);

	//Update the camera to match the screen settings
	camera->width = settings.resolution.x;
	camera->height = settings.resolution.y;
	if (activeScene != nullptr)
	{
		camera->bounds.width = activeScene->sceneWidth;
		camera->bounds.height = activeScene->sceneHeight;
	}
	camera->update();

	window.setKeyRepeatEnabled(false);
}
