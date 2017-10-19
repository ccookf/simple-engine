#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics.hpp>

class Game;
class GameObject;

class AnimationFrame
{
public:
	float duration;
	sf::IntRect textureArea;

	AnimationFrame() { duration = 0; }
	AnimationFrame(float duration, sf::IntRect textureArea) : duration(duration), textureArea(textureArea) {}
};

class Animation
{
public:
	GameObject* parent { nullptr };
	sf::Sprite sprite;
	sf::Texture* texture;
	std::vector<AnimationFrame> frames;
	std::vector<float> frameTimings;

	bool loop { false };
	bool randomized { false };
	bool playing { false };
	float elapsed { 0 };
	float maxDuration;
	int activeFrame { 0 };
	
	Animation();

	void setTexture(sf::Texture* tex)
	{
		texture = tex;
		sprite.setTexture(*tex);
	}
	void setScale(float x, float y) { sprite.setScale(x, y); }
	void setOrigin(float x, float y) { sprite.setOrigin(x, y); }
	void calculateMaxDuration();
	void play();
	void stop();
	void update();

private:
	Game* game {nullptr};
};

#endif
