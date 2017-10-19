#ifndef SCENE_H
#define SCENE_H

//Abstract class for scene loading/unloading
class Scene
{
public:
	virtual void load() = 0;
	virtual void unload() = 0;
};

#endif
