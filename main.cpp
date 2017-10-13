/**
 * Game core
 * 
 * Preprocessor flags "g++ -D flag(=value)":
 *  DEBUG
 */

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <stdlib.h>
#include <thread>
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

int main()
{
	srand(time(NULL));

	#ifdef DEBUG
	std::cout << "Launching debug build...\n";
	#endif
	
	sf::RenderWindow window(sf::VideoMode(800, 600), "Sprite Testing", sf::Style::Close);
	//window.setFramerateLimit(144);

	//player & Light
	sf::Color lightColors[] = {
		sf::Color(255, 0, 0, 255),
		sf::Color(255, 255, 0, 255),
		sf::Color(0, 255, 255, 255),
		sf::Color(255, 0, 255, 255),
		sf::Color(0, 0, 255, 255)
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
	std::map<SpriteLayer, std::vector<GameObject*>> &spriteLayers = spriteLayerManager->map;
	std::map<int, std::vector<CollisionBox*>> &collisionLayers = collisionBoxManager->map;
	std::vector<GameObject*> &gameObjects = GameObject::gameObjects;
	sf::Clock clock;
	FpsCounter fps;

	//Setup the backbuffer and light buffer
	sf::RenderTexture backBuffer;
	backBuffer.create(800, 600);
	sf::Sprite backBufferSprite;
	backBufferSprite.setTexture(backBuffer.getTexture());

	sf::RenderTexture lightBuffer;
	lightBuffer.create(800, 600);

	//Setup the lighting shader
	sf::Shader lightShader;
	lightShader.loadFromFile("assets/multiply-light.frag", sf::Shader::Fragment);
	lightShader.setUniform("lightmap", lightBuffer.getTexture());
	lightShader.setUniform("texture", sf::Shader::CurrentTexture);

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
			for (auto box : collisionLayers[layer])
			{
				//Skip boxes without parents or inactive gameobjects
				if (box->parent == nullptr || !box->parent->active) continue;

				//Check the box against other boxes
				for (auto otherLayer : RegisteredCollisionLayers)
				{
					//Check if the box can interact with the other layer
					if (box->collisionMask & otherLayer)
					{
						for (auto otherBox : collisionLayers[otherLayer])
						{
							box->checkCollision(otherBox);
						}
					}
				}
			}
		}

		//Clear the render textures for drawing
		lightBuffer.clear(sf::Color::Black);
		backBuffer.clear(sf::Color::Black);

		//Drawing all objects, ordered by layer
		for (auto layer : RegisteredSpriteLayers)
		{
			if (layer == SpriteLayer::Lights)
			{
				//Draw all lights to the light buffer
				for (auto obj : spriteLayers[layer])
				{
					obj->Draw(lightBuffer);
				}
			}
			else
			{
				//Draw to back buffer
				for (auto obj : spriteLayers[layer])
				{
					obj->Draw(backBuffer);
				}
			}
		}

		//Apply the light map to the back buffer and draw to window
		window.draw(backBufferSprite, &lightShader);
		
		//Update the fps counter
		fps.Update(deltaTime);
		window.draw(fps.text);

		//End game loop and display new frame
		window.display();
	}

	return 0;
}
