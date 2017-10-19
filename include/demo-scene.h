#ifndef DEMO_SCENE_H
#define DEMO_SCENE_H

#include "background-pic.h"
#include "dude.h"
#include "light.h"
#include "scene.h"
#include "texture-manager.h"

class DemoScene : public Scene
{
public:
	Dude* dudes[5];
	Light* lights[5];
	BackgroundPic* pic;

	void load();
	void unload();
};

#endif
