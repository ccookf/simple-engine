#include "util.h"

#include <stdlib.h>

float randomRange(float a, float b)
{
	float range = b - a;
	float random = ((float) rand()) / (float) RAND_MAX;
	return a + range * random;
}

int randomRnage(int a, int b)
{
	int range = b - a;
	return a + (rand() % range + 1);
}

//Get a random float centered on a range. Eg: range 50 -> [-25, 25]
float randomVariance(float range)
{
	float random = ((float) rand()) / (float) RAND_MAX;
	return range * random - (range / 2.0f);
}

//Random int from [-range/2, range/2]
int randomVariance(int range)
{
	if (range < 1) return 0;
	return rand() % range + 1 - (range / 2);
}