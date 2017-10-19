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

	isLoaded = true;
}

void DemoScene::unload()
{
	if (!isLoaded) return;

	for (int i = 0; i < 5; i++)
	{
		delete dudes[i];
		delete lights[i];
		dudes[i] = nullptr;
		lights[i] = nullptr;
	}
	delete pic;

	isLoaded = false;
}

DemoScene::~DemoScene()
{
	if (isLoaded) unload();
}