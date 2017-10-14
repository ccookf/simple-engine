#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

#include "collision-box.h"
#include "collision-layers.h"

//Static members
CollisionBoxManager* CollisionBoxManager::_instance;

/********************************************************
 * CollisionBox
 *******************************************************/
void CollisionBox::checkCollision(CollisionBox* other)
{	
	if (!box.intersects(other->box)) return;
	parent->onCollision(this, other);
	other->parent->onCollision(other, this);
}

void CollisionBox::setDimensions(float width, float height)
{
	this->height = height;
	this->width = width;
}

void CollisionBox::setOrigin(float x, float y)
{
	origin.x = x;
	origin.y = y;
}

void CollisionBox::setOffset(float x, float y)
{
	parentPositionOffset.x = x;
	parentPositionOffset.y = y;
}

void CollisionBox::update()
{
	sf::Vector2f newOffset = parentPositionOffset - origin;
	
	newOffset.x *= parent->scale.x;
	newOffset.y *= parent->scale.y;

	if (parent != nullptr)
		position = parent->position + newOffset;
	
	box.top = position.y;
	box.left = position.x;
	box.width = width * parent->scale.x;
	box.height = height * parent->scale.y;
}

void CollisionBox::draw(sf::RenderTarget &target)
{
	if (!isVisible) return;
	sf::RectangleShape shape(sf::Vector2f(box.width, box.height));
	shape.setPosition(position);
	shape.setFillColor(color);
	target.draw(shape);
}

/******************************************************
 * Collsion Box Manager
 *****************************************************/

CollisionBoxManager::CollisionBoxManager()
{
	for (auto layer : RegisteredCollisionLayers)
	{
		map.insert(std::make_pair(layer, std::vector<CollisionBox*>()));
	}
}

CollisionBoxManager* CollisionBoxManager::instance()
{
	if (_instance == nullptr) _instance = new CollisionBoxManager();
	return _instance;
}

void CollisionBoxManager::add(int collisionLayer, CollisionBox* box)
{
	map[collisionLayer].push_back(box);
}
