#include "game.h"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

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
#include "texture-manager.h"

Game* Game::_instance;

Game::Game() {}
Game::~Game() {}
Game* Game::instance()
{
	if (_instance == nullptr) _instance = new Game();
	return _instance;
}

void Game::run()
{
	srand(time(NULL));
	
	#ifdef DEBUG
	std::cout << "Launching debug build...\n";
	#endif
	
	sf::RenderWindow window(sf::VideoMode(800, 600), "Sprite Testing", sf::Style::Close);
	//window.setFramerateLimit(144);

	//player & Light
	sf::Color lightColors[] = {
		sf::Color(255, 128, 128, 255),
		sf::Color(255, 255, 128, 255),
		sf::Color(128, 255, 255, 255),
		sf::Color(255, 128, 255, 255),
		sf::Color(128, 128, 255, 255)
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
	std::vector<GameObject*> &gameObjects = GameObject::gameObjects;
	sf::Clock clock;
	FpsCounter fps;

	//Setup the backbuffer and light buffer
	sf::RenderTexture lightBuffer;
	lightBuffer.create(800, 600);
	sf::Sprite lightBufferSprite;
	lightBufferSprite.setTexture(lightBuffer.getTexture());
	lightBufferSprite.setTextureRect(sf::IntRect(0,600,800,-600));

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

		//Multiply the light map onto the window
		window.draw(lightBufferSprite, sf::RenderStates(sf::BlendMultiply));
		
		//Update the fps counter
		fps.Update(deltaTime);
		window.draw(fps.text);

		//End game loop and display new frame
		window.display();
	}
}