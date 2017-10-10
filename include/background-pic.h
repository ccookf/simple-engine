#ifndef BACKGROUND_PIC_H
#define BACKGROUND_PIC_H

#include "gameobject.h"
#include "texture-manager.h"

#include <iostream>

class BackgroundPic : public GameObject
{
public:
	sf::Sprite sprite;
	
	BackgroundPic()
	{
		sprite.setTexture(*TextureManager::getTexture("assets/photo.png"));
	}

	void Draw(sf::RenderTarget &target) 
	{ 
		target.draw(sprite); 
	}
};

#endif
