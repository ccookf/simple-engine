/**
 * Game core
 * 
 * Preprocessor flags "g++ -D flag(=value)":
 *  DEBUG
 */

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>

#include "fps-counter.h"
#include "gameobject.h"
#include "collision-box.h"
#include "texture-manager.h"
#include "dude.h"
#include "background-pic.h"
#include "light.h"

int main()
{
	srand(time(NULL));

	#ifdef DEBUG
	std::cout << "Launching debug build...\n";
	#endif
	
	sf::RenderWindow window(sf::VideoMode(800, 600), "Sprite Testing", sf::Style::Close);
	window.setFramerateLimit(144);

	//player & Light
	Dude* dude = new Dude;
	Light* light = new Light;
	light->setParent(dude);

	//background
	BackgroundPic* pic = new BackgroundPic;

	//Engine maintenance
	std::vector<GameObject*> &gameObjects = GameObject::gameObjects;
	std::vector<CollisionBox*> &collisionBoxes = CollisionBox::boxes;
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
		for (int i = 0; i < collisionBoxes.size(); i++)
		{
			for (int j = 0; j < collisionBoxes.size(); j++)
			{
				if (i == j) continue;
				else if (collisionBoxes[i]->collisionMask & collisionBoxes[j]->mask)
					collisionBoxes[i]->checkCollision(collisionBoxes[j]);
			}
		}

		//Clear the render textures for drawing
		lightBuffer.clear(sf::Color::Black);
		backBuffer.clear(sf::Color::Black);

		//Drawing all objects, ordered by layer
		for (int j = 0; j < spriteLayers.size(); j++)
			for (int i = 0; i < gameObjects.size(); i++)
				if (gameObjects[i]->layer == spriteLayers[j])
				{
					if (gameObjects[i]->layer == SpriteLayer::Lights)
						gameObjects[i]->Draw(lightBuffer);
					else gameObjects[i]->Draw(backBuffer);
				}

		window.draw(backBufferSprite, &lightShader);
		
		//Update the fps counter
		fps.Update(deltaTime);
		window.draw(fps.text);

		//End game loop and display new frame
		window.display();
	}

	return 0;
}
