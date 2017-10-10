#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "gameobject.h"

GameObject::GameObject()
{
	position = sf::Vector2f(0, 0);
	parentPositionOffset = sf::Vector2f(0, 0);
	layer = SpriteLayer::Default;
	gameObjects.push_back(this);
}

GameObject::~GameObject()
{
	for (int i = 0; i < gameObjects.size(); i++)
	{
		if (gameObjects[i] == this) gameObjects.erase(gameObjects.begin()+i);
	}
}

/**
 * Updates acceleration, velocity, and position
 */
void GameObject::PhysicsUpdate(float deltaTime)
{
	velocity += deltaTime * acceleration;
	position += deltaTime * velocity;
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
