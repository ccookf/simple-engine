#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "gameobject.h"

GameObject::GameObject()
{
	game = Game::instance();
	
	//Register the object in the objects list and on the default sprite layer
	gameObjects.push_back(this);
	setLayer(SpriteLayer::Default);
}

GameObject::~GameObject()
{
	for (int i = 0; i < gameObjects.size(); i++)
		if (gameObjects[i] == this) gameObjects.erase(gameObjects.begin()+i);
}

void GameObject::setLayer(SpriteLayer layer)
{
	SpriteLayerManager* slm = SpriteLayerManager::instance();
	slm->remove(this->layer, this);
	slm->add(layer, this);
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
