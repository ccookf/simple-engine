#ifndef SPRITELAYERS_H
#define SPRITELAYERS_H

#include <array>

enum class SpriteLayer : int
{
	Default,
	Player,
	Lights
};

extern std::array<SpriteLayer, 3> spriteLayers;

#endif
