#ifndef COLLISION_LAYERS_H
#define COLLISION_LAYERS_H

enum CollisionLayers
{
	CL_Physics = 1,
	CL_PlayerHitbox = 2,
	CL_PlayerHurtbox = 4,
	CL_EnemyHitbox = 8,
	CL_EnemyHurtbox = 16
};

#endif
