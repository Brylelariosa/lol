#include "engine/video.h"
#include "engine/input.h"
#include "engine/fixed.h"
#include "game/entity.h"
#include "game/player.h"
#include "game/level.h"
#include "game/camera.h"

static Entity player;
static Camera camera;

// Placeholder solid-color art. Swap these for grit-converted PNGs
// (see README) once you're ready for real sprites/tiles - nothing else
// in the codebase needs to change, video.c's upload functions just take
// real tile data instead.
static void setup_graphics(void) {
    video_set_bg_palette(0, RGB15(10, 15, 31));  // sky blue backdrop
    video_upload_bg_tile(0, 0);                  // empty tile (transparent)

    video_set_bg_palette(1, RGB15(8, 20, 8));    // ground green
    video_upload_bg_tile(1, 1);

    video_set_obj_palette(1, RGB15(28, 6, 6));   // player red
    video_upload_obj_tile(0, 1);
}

int main(void) {
    video_init_mode0();
    setup_graphics();

    level_init();
    video_upload_bg_map(level_get_tiles(), LEVEL_TILE_W, LEVEL_TILE_H);

    player_init(&player, FX_FROM_INT(16), FX_FROM_INT(16));
    camera.x = 0;
    camera.y = 0;

    while (1) {
        input_poll();

        player.update(&player);
        camera_follow(&camera, &player, SCREEN_W, SCREEN_H);
        camera_clamp(&camera, level_width_px(), level_height_px(), SCREEN_W, SCREEN_H);

        video_wait_vblank();
        video_set_bg0_scroll(FX_TO_INT(camera.x), FX_TO_INT(camera.y));
        player.draw(&player, 0, &camera);
    }

    return 0;
}
