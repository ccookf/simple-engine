#ifndef SETTINGS_H
#define SETTINGS_H

#include <SFML/System.hpp>

class Settings
{
public:
	
	//Viewport settings
	sf::Vector2i resolution {800, 600};
	bool fullscreen {false};
	bool fpsCapped {false};
	int fpsCap {144};

	//Game settings
	float lightLevel {0.1};					//0 = fully dark, 1 = fully lit

	Settings() {}
	~Settings() {}
};

#endif
