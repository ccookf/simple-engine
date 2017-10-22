#include "demo-scene.h"

#include "audio.h"
#include "camera.h"
#include "dude.h"
#include "game.h"
#include "light.h"
#include "texture-manager.h"

void DemoScene::load()
{
	//Since I don't really want to muck up the engine classes with demo specific code
	//I'm assigning the input here (do not want configurable input here, as that is
	//very game specific).
	Game* game = Game::instance();
	game->input.assignActionToInputPressed(sf::Keyboard::Up, Action_Up_Pressed);
	game->input.assignActionToInputPressed(sf::Keyboard::Down, Action_Down_Pressed);
	game->input.assignActionToInputPressed(sf::Keyboard::Left, Action_Left_Pressed);
	game->input.assignActionToInputPressed(sf::Keyboard::Right, Action_Right_Pressed);

	game->input.assignActionToInputReleased(sf::Keyboard::Up, Action_Up_Released);
	game->input.assignActionToInputReleased(sf::Keyboard::Down, Action_Down_Released);
	game->input.assignActionToInputReleased(sf::Keyboard::Left, Action_Left_Released);
	game->input.assignActionToInputReleased(sf::Keyboard::Right, Action_Right_Released);
	
	game->input.assignActionToInputPressed(sf::Keyboard::Space, Action_Special_Ability_1);

	//player & Light
	sf::Color lightColors[] = 
	{
		sf::Color(255, 128, 128, 64),
		sf::Color(255, 255, 128, 64),
		sf::Color(128, 255, 255, 64),
		sf::Color(255, 128, 255, 64),
		sf::Color(128, 128, 255, 64)
	};

	for (int i = 0; i < 5; i++)
	{
		dudes[i] = new Dude;
		dudes[i]->position = sf::Vector2f(100*i, 100*i);
		lights[i] = new Light;
		lights[i]->setParent(dudes[i]);
		lights[i]->color = lightColors[i];
	}

	int area[] = 
	{
		89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 
		89, 90, 90, 90, 89, 89, 90, 90, 90, 89, 89, 90, 90, 90, 89, 89, 90, 90, 90, 89, 
		89, 90, 88, 90, 89, 89, 90, 88, 90, 89, 89, 90, 88, 90, 89, 89, 90, 88, 90, 89, 
		89, 90, 90, 90, 89, 89, 90, 90, 90, 89, 89, 90, 90, 90, 89, 89, 90, 90, 90, 89, 
		89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 
		89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 
		89, 90, 90, 90, 89, 89, 90, 90, 90, 89, 89, 90, 90, 90, 89, 89, 90, 90, 90, 89, 
		89, 90, 88, 90, 89, 89, 90, 88, 90, 89, 89, 90, 88, 90, 89, 89, 90, 88, 90, 89, 
		89, 90, 90, 90, 89, 89, 90, 90, 90, 89, 89, 90, 90, 90, 89, 89, 90, 90, 90, 89, 
		89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 
		89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 
		89, 90, 90, 90, 89, 89, 90, 90, 90, 89, 89, 90, 90, 90, 89, 89, 90, 90, 90, 89, 
		89, 90, 88, 90, 89, 89, 90, 88, 90, 89, 89, 90, 88, 90, 89, 89, 90, 88, 90, 89, 
		89, 90, 90, 90, 89, 89, 90, 90, 90, 89, 89, 90, 90, 90, 89, 89, 90, 90, 90, 89, 
		89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 
		89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 
		89, 90, 90, 90, 89, 89, 90, 90, 90, 89, 89, 90, 90, 90, 89, 89, 90, 90, 90, 89, 
		89, 90, 88, 90, 89, 89, 90, 88, 90, 89, 89, 90, 88, 90, 89, 89, 90, 88, 90, 89, 
		89, 90, 90, 90, 89, 89, 90, 90, 90, 89, 89, 90, 90, 90, 89, 89, 90, 90, 90, 89, 
		89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89 
	};

	room = new TileMap
	(
		TextureManager::getTexture("assets/tilesheet.png"),
		sf::Vector2i(64, 64),
		8,
		13,
		area,
		20,
		20
	);

	sceneWidth = 20 * 64;
	sceneHeight = 20 * 64;

	//Set the camera to person
	Camera* camera = game->camera;
	camera->target = dudes[2];
	camera->bounds.width = sceneWidth;
	camera->bounds.height = sceneHeight;

	//Load some music
	Audio::instance()->bgm.openFromFile("assets/database.ogg");
	Audio::instance()->bgm.setVolume(50);
	Audio::instance()->bgm.play();

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

	delete room;

	Audio::instance()->bgm.stop();

	isLoaded = false;
}

DemoScene::~DemoScene()
{
	if (isLoaded) unload();
}