#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

#include "collision-box.h"

std::vector<CollisionBox*> CollisionBox::boxes;

CollisionBox::CollisionBox()
{
	boxes.push_back(this);
}

CollisionBox::~CollisionBox()
{
	for (int i = 0; i < boxes.size(); i++)
		if (boxes[i] == this) boxes.erase(boxes.begin()+i);
}

void CollisionBox::checkCollision(CollisionBox* other)
{	
	if (!box.intersects(other->box)) return;
	parent->OnCollision(this, other);
	other->parent->OnCollision(other, this);
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

void CollisionBox::Update()
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

void CollisionBox::Draw(sf::RenderTarget &target)
{
	if (!isVisible) return;
	return;
	sf::RectangleShape shape(sf::Vector2f(box.width, box.height));
	shape.setPosition(position);
	shape.setFillColor(color);
	target.draw(shape);
}
