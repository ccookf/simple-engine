#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <vector>

#include "gameobject.h"
#include "animation.h"

/**
 * Calculates the max duration based supplied frame data
 * and sets the cumulative frame timings
 */
void Animation::calculateMaxDuration()
{
	if (frames.size() == 0) { maxDuration = 0; return; }

	float duration = 0;
	for (int i = 0; i < frames.size(); i++)
	{
		frameTimings.push_back(duration);
		duration += frames[i].duration;
	}
	maxDuration = duration;
	//Initialize the texture rectangle 
	sprite.setTextureRect(frames[0].textureArea);
}

/**
 * Resets and starts animation.
 */
void Animation::play()
{
	playing = true;
	elapsed = 0;
	activeFrame = 0;

	if (randomized && maxDuration > 0)
	{
		float random = ((float) rand()) / ((float) RAND_MAX);
		elapsed = maxDuration * random;

		for (int i = 0; i < frameTimings.size(); i++)
			if (elapsed >= frameTimings[i]) activeFrame = i;
	}

	sprite.setTextureRect(frames[activeFrame].textureArea);
}

/**
 * Halts the animation
 */
void Animation::stop()
{
	playing = false;
}

/**
 * Progresses the animation based on the elapsed and changed time
 */
void Animation::Update(float deltaTime)
{
	if (!playing) return;
	
	//Update the time and reset if looping
	elapsed += deltaTime;
	if (loop && elapsed > maxDuration)
		elapsed -= maxDuration;

	//Compared the elapsed time to the absolute frame timings
	for (int i = 0; i < frameTimings.size(); i++)
		if (elapsed >= frameTimings[i]) activeFrame = i;

	//Update the sprite to the current active frame
	sprite.setTextureRect(frames[activeFrame].textureArea);

	//Set the scale to match the parent gameobject if it exists
	if (parent != nullptr) sprite.setScale(parent->scale);
}
