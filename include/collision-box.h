#ifndef COLLISION_BOX_H
#define COLLISION_BOX_H

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "gameobject.h"

class GameObject;

class CollisionBox
{
public:
	sf::FloatRect box;
	float width {0};
	float height {0};
	int mask {0};
	int collisionMask {0};
	sf::Vector2f position {0, 0};
	sf::Vector2f origin {0, 0};
	sf::Vector2f parentPositionOffset {0, 0};

	bool isVisible {false};
	sf::Color color {sf::Color(0,0,255,128)};

	GameObject* parent { nullptr };

	CollisionBox();
	~CollisionBox();

	void Update();
	void Draw(sf::RenderTarget &target);
	void setDimensions(float width, float height);
	void setOrigin(float x, float y);
	void setOffset(float x, float y);
	void checkCollision(CollisionBox* other);

	static std::vector<CollisionBox*> boxes;
};

#endif
