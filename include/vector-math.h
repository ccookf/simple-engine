#ifndef VECTORMATH_H
#define VECTORMATH_H

inline float mag(float x, float y)
{
	return sqrt(x*x + y*y);
}

inline float mag(sf::Vector2f vec)
{
	return sqrt(vec.x*vec.x + vec.y*vec.y);
}

#endif
