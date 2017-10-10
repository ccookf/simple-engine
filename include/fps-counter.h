#ifndef FPSCOUNTER_H
#define FPSCOUNTER_H

#include <deque> //I have no idea why this needs to be in the header

class FpsCounter
{
public:
	sf::Font font;
	sf::Text text;
	std::deque<float> samples;

	float elapsed;
	float interval;
	
	FpsCounter();
	void Update(float time);
};

#endif
