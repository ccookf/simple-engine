#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <vector>
#include <forward_list>

#include "sprite-layers.h"
#include "collision-box.h"

class CollisionBox;

class GameObject
{
public:
	sf::Vector2f position { 0, 0 };
	sf::Vector2f velocity { 0, 0 };
	sf::Vector2f acceleration { 0, 0 };
	sf::Vector2f scale { 1, 1 };

	sf::Vector2f parentPositionOffset { 0, 0 };
	SpriteLayer layer { SpriteLayer::Default };

	GameObject();
	~GameObject();
	virtual void Update(float deltaTime) {}
	virtual void Draw(sf::RenderTarget &target) {}
	void PhysicsUpdate(float deltaTime);
	virtual void OnCollision(CollisionBox* own, CollisionBox* other) {}

	//Parent-Child relationship functions
	void setParent(GameObject* parent);
	void removeParent();
	void addChild(GameObject* child);
	void removeChild(GameObject* child);
	void removeAllChildren();
	void updateChildrenTransform();

	//Static Members
	static std::vector<GameObject*> gameObjects;

private:
	GameObject* parent;
	std::forward_list<GameObject*> children;
};

#endif