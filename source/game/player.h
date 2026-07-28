#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H

#include "entity.h"

void player_init(Entity* player, Fixed start_x, Fixed start_y);

// Matches EntityUpdateFn / EntityDrawFn - assign directly to
// player.update / player.draw so the main loop can treat the player
// like any other entity.
void player_update(Entity* self);
void player_draw(Entity* self, int oam_slot, const struct Camera* cam);

#endif
