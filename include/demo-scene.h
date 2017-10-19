#ifndef DEMO_SCENE_H
#define DEMO_SCENE_H

#include "dude.h"
#include "light.h"
#include "scene.h"
#include "texture-manager.h"
#include "tilemap.h"

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
