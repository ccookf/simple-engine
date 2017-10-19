/**
 * This is the main camera that sets the game viewport.
 * Currently only intending for a single camera, single viewport.
 **/

#ifndef CAMERA_H
#define CAMERA_H

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

class GameObject;

class Camera
{
public:
	sf::Vector2f position {400, 300}; //centered camera position
	sf::Vector2f offset {0, 0};
	int width {800};
	int height {600};
	sf::IntRect bounds {0, 0, 800, 600};
	GameObject* target {nullptr};

	void update();

private:
	sf::View view;
};

#endif
