#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <deque>
#include "fps-counter.h"
#include "tostring.h"

#define SAMPLES 144
#define UPDATE_TICKS 144

FpsCounter::FpsCounter()
{
	font.loadFromFile("assets/amiko/Amiko-Regular.ttf");

	text.setFont(font);
	text.setString("0");
	text.setCharacterSize(12);
	text.setPosition(sf::Vector2f(0, 0));
	text.setFillColor(sf::Color::White);

	elapsed = 0;
	interval = 0.5;
}

void FpsCounter::update(float deltaTime)
{
	samples.push_back(deltaTime);
	if (samples.size() > SAMPLES) samples.pop_front();
	
	//Find average of samples
	float total = 0;
	for (int i = 0; i < samples.size(); i++)
		total += samples[i];

	float average = total/samples.size();

	//Update when enough time has passed
	elapsed += deltaTime;
	if (elapsed >= interval)
	{
		text.setString(toString(static_cast<int>(1.0/average)));
		elapsed -= interval;
	}		
};
