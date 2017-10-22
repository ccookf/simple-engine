#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <forward_list>

#include "game.h"
#include "sprite-layers.h"

//Forward declarations
class CollisionBox;

class GameObject
{
public:
	bool active { true };
	sf::Vector2f position { 0, 0 };
	sf::Vector2f velocity { 0, 0 };
	sf::Vector2f acceleration { 0, 0 };
	sf::Vector2f scale { 1, 1 };

	sf::Vector2f parentPositionOffset { 0, 0 };

	GameObject();
	~GameObject();
	void setLayer(int spriteLayer);
	virtual void update() {}
	virtual void draw(sf::RenderTarget &target) {}
	void physicsUpdate();
	virtual void onCollision(CollisionBox* own, CollisionBox* other) {}

	//Parent-Child relationship functions
	void setParent(GameObject* parent);
	void removeParent();
	void addChild(GameObject* child);
	void removeChild(GameObject* child);
	void removeAllChildren();
	void updateChildrenTransform();

	//Static Members
	static std::vector<GameObject*> gameObjects;

protected:
	Game* game {nullptr};

private:
	int spriteLayer {0}; //SL_Default = 0
	GameObject* parent {nullptr};
	std::forward_list<GameObject*> children; // @todo - this shouldn't be a flist
};

#endif