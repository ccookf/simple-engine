#include "sprite-layers.h"

std::vector<SpriteLayer> RegisteredSpriteLayers = 
{
	SpriteLayer::Default,
	SpriteLayer::Player,
	SpriteLayer::Lights
};

//Static member initialization
SpriteLayerManager* SpriteLayerManager::_instance;

//Constructor
//Generate vectors on class load instead of runtime
SpriteLayerManager::SpriteLayerManager()
{
	for (auto layer : RegisteredSpriteLayers)
	{
		map.insert(std::make_pair(layer, std::vector<GameObject*>()));
	}
}

//Singleton entrance
SpriteLayerManager* SpriteLayerManager::instance()
{
	if (_instance == nullptr) _instance = new SpriteLayerManager();
	return _instance;
}

void SpriteLayerManager::add(SpriteLayer layer, GameObject* obj)
{
	map[layer].push_back(obj);
}

//Returns false if the object is not in the layer
bool SpriteLayerManager::remove(SpriteLayer layer, GameObject* obj)
{
	std::vector<GameObject*> vec = map[layer];
	for (int i = 0; i < vec.size(); i++)
	{
		if (vec[i] == obj)
		{
			vec.erase(vec.begin()+i);
			return true;
		}
	}
	return false;
}
