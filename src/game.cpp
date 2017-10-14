#include "game.h"

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>

#include "background-pic.h"
#include "collision-box.h"
#include "collision-layers.h"
#include "dude.h"
#include "fps-counter.h"
#include "gameobject.h"
#include "light.h"
#include "particle-manager.h"
#include "texture-manager.h"

Game* Game::_instance;

Game::Game(sf::RenderWindow& window) : window(window) {}
Game::~Game() {}
Game* Game::instance(sf::RenderWindow& window)
{
	if (_instance == nullptr) _instance = new Game(window);
	return _instance;
}

void Game::run()
{
	srand(time(NULL));
	
	#ifdef DEBUG
	std::cout << "Launching debug build...\n";
	#endif
	
	resetWindow();

	//player & Light
	sf::Color lightColors[] = {
		sf::Color(255, 128, 128, 128),
		sf::Color(255, 255, 128, 128),
		sf::Color(128, 255, 255, 128),
		sf::Color(255, 128, 255, 128),
		sf::Color(128, 128, 255, 128)
	};
	for (int i = 0; i < 5; i++)
	{
		Dude* dude = new Dude;
		dude->position = sf::Vector2f(100*i, 100*i);
		Light* light = new Light;
		light->setParent(dude);
		light->color = lightColors[i];
	}

	//background
	BackgroundPic* pic = new BackgroundPic;

	//Engine maintenance
	SpriteLayerManager* spriteLayerManager = SpriteLayerManager::instance();
	CollisionBoxManager* collisionBoxManager = CollisionBoxManager::instance();
	ParticleManager* particleManager = ParticleManager::instance();
	std::vector<GameObject*> &gameObjects = GameObject::gameObjects;
	sf::Clock clock;
	FpsCounter fps;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
					window.close();

				if (event.key.code == sf::Keyboard::F1)
				{
					settings.resolution.x = 1600;
					settings.resolution.y = 900;
					settings.fullscreen = false;
					resetWindow();
				}
				if (event.key.code == sf::Keyboard::F2)
				{
					settings.resolution.x = 800;
					settings.resolution.y = 600;
					settings.fullscreen = false;
					resetWindow();
				}
			}
		}

		//Update all GameObjects
		float deltaTime = clock.restart().asSeconds();
		for (int i = 0; i < gameObjects.size(); i++)
			gameObjects[i]->Update(deltaTime);

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
		lightBuffer.clear(sf::Color::Black);

		//Drawing all objects, ordered by layer
		for (auto layer : RegisteredSpriteLayers)
		{
			if (layer == SpriteLayer::Lights)
			{
				//Draw all lights to the light buffer
				for (auto obj : spriteLayerManager->map[layer])
				{
					obj->Draw(lightBuffer);
				}
			}
			else
			{
				//Draw to back buffer
				for (auto obj : spriteLayerManager->map[layer])
				{
					obj->Draw(window);
				}
			}
		}

		//Update and draw all particles
		particleManager->updateAndDraw(deltaTime, lightBuffer);

		//Multiply the light map onto the window
		window.draw(lightBufferSprite, sf::RenderStates(sf::BlendMultiply));
		
		//Update the fps counter
		fps.Update(deltaTime);
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
}
