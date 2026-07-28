#include "level.h"

static uint16_t s_tiles[LEVEL_TILE_H][LEVEL_TILE_W];

static void fill_rect(int x0, int y0, int x1, int y1, uint16_t tile) {
    for (int y = y0; y <= y1; y++) {
        if (y < 0 || y >= LEVEL_TILE_H) continue;
        for (int x = x0; x <= x1; x++) {
            if (x < 0 || x >= LEVEL_TILE_W) continue;
            s_tiles[y][x] = tile;
        }
    }
}

void level_init(void) {
    fill_rect(0, 0, LEVEL_TILE_W - 1, LEVEL_TILE_H - 1, TILE_EMPTY);

    // ground strip along the bottom
    fill_rect(0, LEVEL_TILE_H - 4, LEVEL_TILE_W - 1, LEVEL_TILE_H - 1, TILE_GROUND);

    // a gap you have to jump over
    fill_rect(14, LEVEL_TILE_H - 4, 16, LEVEL_TILE_H - 1, TILE_EMPTY);

    // a couple of floating platforms
    fill_rect(6, LEVEL_TILE_H - 8, 9, LEVEL_TILE_H - 8, TILE_GROUND);
    fill_rect(20, LEVEL_TILE_H - 10, 24, LEVEL_TILE_H - 10, TILE_GROUND);
}

const uint16_t* level_get_tiles(void) {
    return &s_tiles[0][0];
}

int level_is_solid_px(int px_x, int px_y) {
    if (px_x < 0 || px_y < 0) return 1;
    int tx = px_x / TILE_PX;
    int ty = px_y / TILE_PX;
    if (tx >= LEVEL_TILE_W || ty >= LEVEL_TILE_H) return 1;
    return s_tiles[ty][tx] != TILE_EMPTY;
}

int level_width_px(void)  { return LEVEL_TILE_W * TILE_PX; }
int level_height_px(void) { return LEVEL_TILE_H * TILE_PX; }
