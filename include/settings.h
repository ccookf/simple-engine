#ifndef SETTINGS_H
#define SETTINGS_H

#include <SFML/System.hpp>

class Settings
{
public:

	sf::Vector2i resolution {800, 600};
	bool fullscreen {false};

	Settings() {}
	~Settings() {}
};

#endif
