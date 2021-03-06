#ifndef COLLISION_BOX_H
#define COLLISION_BOX_H

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <map>
#include <vector>

class GameObject;

class CollisionBox
{
public:
	sf::FloatRect box;
	float width {0};
	float height {0};
	int collisionMask {0};
	sf::Vector2f position {0, 0};
	sf::Vector2f origin {0, 0};
	sf::Vector2f parentPositionOffset {0, 0};

	bool isVisible {false};
	sf::Color color {sf::Color(0,0,255,128)};

	GameObject* parent { nullptr };

	void update();
	void draw(sf::RenderTarget &target);
	void setDimensions(float width, float height);
	void setOrigin(float x, float y);
	void setOffset(float x, float y);
	void checkCollision(CollisionBox* other);
};

//Should collision boxes be stored on the object or an array?
//Is a vector actually appropriate here?
class CollisionBoxManager
{
public:
	std::map<int, std::vector<CollisionBox*>> map;

	CollisionBoxManager();
	static CollisionBoxManager* instance();
	void add(int collisionLayer, CollisionBox* box);
	bool remove(int collisionLayer, CollisionBox* box);

private:
	static CollisionBoxManager* _instance;
};

#endif
