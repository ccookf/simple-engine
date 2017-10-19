#ifndef DEMO_SCENE_H
#define DEMO_SCENE_H

#include "scene.h"
#include "tilemap.h"

class Dude;
class Light;

class DemoScene : public Scene
{
public:
	Dude* dudes[5];
	Light* lights[5];
	TileMap room;

	void load();
	void unload();
	DemoScene() { name = "DemoScene"; }
	~DemoScene();
};

#endif
