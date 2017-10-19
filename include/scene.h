#ifndef SCENE_H
#define SCENE_H

#include <string>

//Abstract class for scene loading/unloading
class Scene
{
public:
	std::string name {"Scene"};
	bool isLoaded {false};
	virtual void load() = 0;
	virtual void unload() = 0;
};

#endif
