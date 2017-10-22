#include "audio.h"

#include <iostream>

//Singleton
Audio* Audio::_instance = nullptr;
Audio* Audio::instance()
{
	if (_instance == nullptr) _instance = new Audio();
	return _instance;
}

sf::Sound* Audio::getSfxChannel(std::string filename)
{
	//Avoid loading at runtime if possible
	if (loadedSfx.count(filename) == 0)
	{
		loadSfx(filename);
		std::cout << filename << " was loaded on demand.\n";
	}

	//Limit audio channels
	if (channels.size() >= MAX_AUDIO_CHANNELS)
	{
		std::cout 	<< "Failed to create sound channel (" << filename
					<< "): All channels are filled.\n";
		return nullptr;
	}

	//Create the sound channel and set its sound buffer
	sf::Sound* channel = new sf::Sound();
	channels.push_back(channel);
	channel->setBuffer(*loadedSfx[filename]);
	return channel;
}

void Audio::releaseSfxChannel(sf::Sound* channel)
{
	for (int i = 0; i < channels.size(); i++)
	{
		if (channels[i] == channel) channels.erase(channels.begin()+i);
	}
}

void Audio::loadSfx(std::string filename)
{
	//Load only if the file isn't already mapped
	if (loadedSfx.count(filename) == 0)
	{
		loadedSfx.insert(std::pair<std::string, sf::SoundBuffer*>(filename, new sf::SoundBuffer()));
		loadedSfx[filename]->loadFromFile(filename);
	}
}

void Audio::playSfx
(
	std::string filename,
	float pitch,
	float volume,
	bool spatial,
	sf::Vector3f position
)
{
	//Avoid loading at runtime if possible
	if (loadedSfx.count(filename) == 0)
	{
		loadSfx(filename);
		std::cout << filename << " was loaded on demand.\n";
	}

	sf::Sound sound;
	sound.setBuffer(*loadedSfx[filename]);
	sound.setPitch(pitch);
	sound.setVolume(volume);
	sound.setRelativeToListener(spatial);
	sound.setPosition(position);
	sounds.push_front(sound);
	sounds.front().play();
}

void Audio::unloadSounds()
{
	//Wipe sound effects
	while (!sounds.empty())
	{
		sounds.pop_front();
	}
	//Delete active channels
	for (int i = channels.size() - 1; i >= 0; --i)
	{
		delete channels[i];
		channels.erase(channels.begin()+i);
	}
	//Clear the loaded sounds in memory
	loadedSfx.clear();
}

bool cullSound(const sf::Sound& sound)
{
	if (sound.getStatus() == sf::Sound::Stopped) return true;
}

void Audio::update()
{
	sounds.remove_if(cullSound);
}
