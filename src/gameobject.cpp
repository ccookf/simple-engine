#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "gameobject.h"

#ifdef DEBUG
#include <iostream>
#endif

GameObject::GameObject()
{
	game = Game::instance();
	
	//Register the object in the objects list and on the default sprite layer
	gameObjects.push_back(this);
	setLayer(SL_Default);
}

GameObject::~GameObject()
{
	for (int i = 0; i < gameObjects.size(); i++)
		if (gameObjects[i] == this) gameObjects.erase(gameObjects.begin()+i);

	SpriteLayerManager* slm = SpriteLayerManager::instance();
	bool res = slm->remove(spriteLayer, this);

	#ifdef DEBUG
	if (res == false) std::cout << "Failed to remove from sprite layer. Crash incoming!\n";
	#endif
}

void GameObject::setLayer(int spriteLayer)
{
	SpriteLayerManager* slm = SpriteLayerManager::instance();
	slm->remove(this->spriteLayer, this);
	slm->add(spriteLayer, this);
	this->spriteLayer = spriteLayer;
}

/**
 * Updates acceleration, velocity, and position
 */
void GameObject::physicsUpdate()
{
	velocity += Game::deltaTime * acceleration;
	position += Game::deltaTime * velocity;
	updateChildrenTransform();
}

void GameObject::setParent(GameObject* parent)
{
	this->parent = parent;
	parent->children.push_front(this);
}

void GameObject::removeParent()
{
	parent->children.remove(this);
	this->parent = nullptr;
}

//Alias for the parent function, meant for convenience
void GameObject::addChild(GameObject* child)
{
	child->setParent(this);
}

//Alias for the parent function, meant for convenience
void GameObject::removeChild(GameObject* child)
{
	child->removeParent();
}

void GameObject::removeAllChildren()
{
	for (GameObject* child : children)
		child->removeParent();
}

void GameObject::updateChildrenTransform()
{
	for (GameObject* child : children)
		child->position = position + child->parentPositionOffset;
}

std::vector<GameObject*> GameObject::gameObjects;
