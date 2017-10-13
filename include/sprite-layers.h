#ifndef SPRITELAYERS_H
#define SPRITELAYERS_H

#include <map>
#include <vector>
#include "gameobject.h"

enum class SpriteLayer
{
	Default,
	Player,
	Lights
};

extern std::vector<SpriteLayer> RegisteredSpriteLayers;

class GameObject;

//Singleton
class SpriteLayerManager
{
public:
	static SpriteLayerManager* _instance;
	std::map<SpriteLayer, std::vector<GameObject*>> map;

	SpriteLayerManager();
	static SpriteLayerManager* instance();
	void add(SpriteLayer layer, GameObject* obj);
	bool remove(SpriteLayer layer, GameObject* obj);
};

#endif
