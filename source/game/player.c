#include "player.h"
#include "physics.h"
#include "camera.h"
#include "../engine/input.h"
#include "../engine/video.h"

#define PLAYER_TILE_INDEX 0  // OBJ VRAM tile 0, uploaded once at startup
#define PLAYER_PALETTE    0

void player_init(Entity* p, Fixed start_x, Fixed start_y) {
    p->x = start_x;
    p->y = start_y;
    p->vx = 0;
    p->vy = 0;
    p->w = 8;
    p->h = 8;
    p->flags = ENT_FLAG_ACTIVE;
    p->oam_slot = 0;
    p->update = player_update;
    p->draw = player_draw;
}

void player_update(Entity* self) {
    self->vx = 0;
    if (input_is_down(KEY_LEFT)) {
        self->vx = -MOVE_SPEED;
        self->flags |= ENT_FLAG_FACING_L;
    } else if (input_is_down(KEY_RIGHT)) {
        self->vx = MOVE_SPEED;
        self->flags &= ~ENT_FLAG_FACING_L;
    }

    if (input_was_pressed(KEY_A) && (self->flags & ENT_FLAG_ON_GROUND)) {
        self->vy = JUMP_SPEED;
    }

    physics_apply_gravity(self);
    physics_move_and_collide(self);
}

void player_draw(Entity* self, int oam_slot, const struct Camera* cam) {
    const Camera* c = (const Camera*)cam;
    int screen_x = FX_TO_INT(self->x) - FX_TO_INT(c->x);
    int screen_y = FX_TO_INT(self->y) - FX_TO_INT(c->y);
    int hflip = (self->flags & ENT_FLAG_FACING_L) ? 1 : 0;
    video_oam_set(oam_slot, screen_x, screen_y, PLAYER_TILE_INDEX, hflip, PLAYER_PALETTE);
}
