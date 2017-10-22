#ifndef AUDIO_H
#define AUDIO_H

#include <SFML/Audio.hpp>
#include <list>
#include <map>
#include <string>
#include <vector>

//These could be set higher, but a new sound system should be setup if 
//sound channels are actually a constraint
#define MAX_AUDIO_CHANNELS 50
#define MAX_CONCURRENT_SFX 100

class Audio
{
public:

	sf::Music bgm;

	static Audio* instance();
	sf::Sound* getSfxChannel(std::string filename);
	void releaseSfxChannel(sf::Sound* channel);
	void loadSfx(std::string filename);
	void playSfx
	(
		std::string filename,
		float pitch = 1.0,
		float volume = 50,
		bool spatial = false,
		sf::Vector3f position = sf::Listener::getPosition()
	);
	void unloadSounds();
	void update();

private:
	Audio() {};
	~Audio() { unloadSounds(); }
	static Audio* _instance;

	std::map<std::string, sf::SoundBuffer*> loadedSfx;
	std::vector<sf::Sound*> channels;
	std::list<sf::Sound> sounds;
};

#endif
