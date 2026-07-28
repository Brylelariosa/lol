#include "physics.h"
#include "level.h"

void physics_apply_gravity(Entity* e) {
    e->vy += GRAVITY;
    if (e->vy > MAX_FALL_SPEED) e->vy = MAX_FALL_SPEED;
}

static int entity_collides_at(const Entity* e, int px_x, int px_y) {
    int x0 = px_x;
    int x1 = px_x + e->w - 1;
    int y0 = px_y;
    int y1 = px_y + e->h - 1;
    return level_is_solid_px(x0, y0) || level_is_solid_px(x1, y0)
        || level_is_solid_px(x0, y1) || level_is_solid_px(x1, y1);
}

static void resolve_axis_x(Entity* e) {
    int px_x = FX_TO_INT(e->x);
    int px_y = FX_TO_INT(e->y);
    if (entity_collides_at(e, px_x, px_y)) {
        if (e->vx > 0) {
            px_x -= (px_x + e->w) % 8;         // snap left edge to tile boundary
        } else if (e->vx < 0) {
            px_x += (8 - (px_x % 8)) % 8;       // snap right edge to tile boundary
        }
        e->x = FX_FROM_INT(px_x);
        e->vx = 0;
    }
}

static void resolve_axis_y(Entity* e) {
    int px_x = FX_TO_INT(e->x);
    int px_y = FX_TO_INT(e->y);
    if (entity_collides_at(e, px_x, px_y)) {
        if (e->vy > 0) {
            px_y -= (px_y + e->h) % 8;
            e->flags |= ENT_FLAG_ON_GROUND;
        } else if (e->vy < 0) {
            px_y += (8 - (px_y % 8)) % 8;
        }
        e->y = FX_FROM_INT(px_y);
        e->vy = 0;
    } else {
        e->flags &= ~ENT_FLAG_ON_GROUND;
    }
}

void physics_move_and_collide(Entity* e) {
    e->x += e->vx;
    resolve_axis_x(e);

    e->y += e->vy;
    resolve_axis_y(e);
}
