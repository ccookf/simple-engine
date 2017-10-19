#include "camera.h"
#include "gameobject.h"
#include "game.h"

void Camera::update()
{
	if (target != nullptr)
	{
		position = target->position;
	}
	
	//Apply offset
	sf::Vector2f pos(position + offset);

	//Check if bounds are smaller than the view dimensions
	if (bounds.width < width) bounds.width = width;
	if (bounds.height < height) bounds.height = height;

	//Enforce camera in boundaries
	//Remember position is centered!
	if ((pos.x - width/2) < bounds.left) //too far left
		pos.x = bounds.left + width/2;
	if ((pos.x + width/2) > bounds.left + bounds.width) //too far right
		pos.x = bounds.left + bounds.width - width/2;
	if ((pos.y - height/2) < bounds.top) //too far up
		pos.y = bounds.top + height/2;
	if ((pos.y + height/2) > bounds.top + bounds.height) //too far down
		pos.y = bounds.top + bounds.height - height/2;
	
	view.setCenter(pos);
	view.setSize(width, height);

	//Apply the viewport
	Game::instance()->window.setView(view);
}