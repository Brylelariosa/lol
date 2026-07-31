#ifndef GAME_PHYSICS_H
#define GAME_PHYSICS_H

#include "entity.h"
#include "../engine/fixed.h"

#define GRAVITY        FX_FRAC(1, 4)   // px/frame^2 downward accel
#define MAX_FALL_SPEED FX_FROM_INT(6)
#define MOVE_SPEED     FX_FROM_INT(2)
#define JUMP_SPEED     FX_FROM_INT(-5)

void physics_apply_gravity(Entity* e);

// Moves the entity by its velocity and resolves collisions against the
// level's tilemap, one axis at a time (X then Y) - the standard approach
// for simple tile-based platformer collision.
void physics_move_and_collide(Entity* e);

#endif
