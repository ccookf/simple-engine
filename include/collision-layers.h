#ifndef COLLISION_LAYERS_H
#define COLLISION_LAYERS_H

#include <vector>

enum CollisionLayers
{
	//No collision = 0,
	CL_Physics = 1,
	CL_PlayerHitbox = 2,
	CL_PlayerHurtbox = 4,
	CL_EnemyHitbox = 8,
	CL_EnemyHurtbox = 16
};

extern std::vector<int> RegisteredCollisionLayers;

#endif
