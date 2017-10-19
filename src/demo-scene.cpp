#include "demo-scene.h"

void DemoScene::load()
{
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
		dudes[i] = new Dude;
		dudes[i]->position = sf::Vector2f(100*i, 100*i);
		lights[i] = new Light;
		lights[i]->setParent(dudes[i]);
		lights[i]->color = lightColors[i];
	}

	pic = new BackgroundPic;
}

void DemoScene::unload()
{
	for (int i = 0; i < 5; i++)
	{
		delete dudes[i];
		delete lights[i];
	}
	delete pic;
}