#ifndef GAME_LEVEL_H
#define GAME_LEVEL_H

#include <stdint.h>

// One screen-block (32x32 tiles = 256x256px) - fits BG regsize 0 with no
// tile-streaming needed. This gives a little real horizontal/vertical scroll
// room over the 240x160 screen. Bump to a bigger regsize + streaming later
// if you want longer levels.
#define LEVEL_TILE_W 32
#define LEVEL_TILE_H 32
#define TILE_PX      8

enum {
    TILE_EMPTY  = 0,
    TILE_GROUND = 1,
};

// Builds the test level into an internal buffer.
void level_init(void);

// Raw tile grid, row-major, LEVEL_TILE_W*LEVEL_TILE_H entries. Hand this to
// video_upload_bg_map().
const uint16_t* level_get_tiles(void);

// Is the tile under this pixel coordinate solid? Out-of-bounds counts as solid.
int level_is_solid_px(int px_x, int px_y);

int level_width_px(void);
int level_height_px(void);

#endif
