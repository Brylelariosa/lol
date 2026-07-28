#ifndef GAME_ENTITY_H
#define GAME_ENTITY_H

#include "../engine/fixed.h"
#include <stdint.h>

typedef struct Entity Entity;
struct Camera; // opaque forward decl - see camera.h. Keeps this header
                // independent of camera.h (no circular include).

typedef void (*EntityUpdateFn)(Entity* self);
typedef void (*EntityDrawFn)(Entity* self, int oam_slot, const struct Camera* cam);

// Minimal entity: no heap allocation (GBA has no OS/malloc to speak of by
// default), just plain structs with function-pointer "virtual methods" for
// per-type behavior. Add new entity types by writing update/draw functions
// with these exact signatures - the game loop doesn't need to know about them.
struct Entity {
    Fixed x, y;    // world position, Q8.8 pixels
    Fixed vx, vy;  // velocity, Q8.8 pixels/frame
    int16_t w, h;  // bounding box, pixels
    uint8_t flags;
    uint8_t oam_slot;
    EntityUpdateFn update;
    EntityDrawFn draw;
};

enum {
    ENT_FLAG_ACTIVE    = 1 << 0,
    ENT_FLAG_ON_GROUND = 1 << 1,
    ENT_FLAG_FACING_L  = 1 << 2,
};

#endif
