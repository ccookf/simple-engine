#ifndef SPRITELAYERS_H
#define SPRITELAYERS_H

#include <map>
#include <vector>
#include "gameobject.h"

enum SpriteLayer
{
	SL_Default = 0,
	SL_Player = 1,
	SL_Lights = 2
};

extern std::vector<SpriteLayer> RegisteredSpriteLayers;

class GameObject;

//Singleton
class SpriteLayerManager
{
public:
	static SpriteLayerManager* _instance;
	std::map<int, std::vector<GameObject*>> map;

	SpriteLayerManager();
	static SpriteLayerManager* instance();
	void add(int layer, GameObject* obj);
	bool remove(int layer, GameObject* obj);
};

#endif
