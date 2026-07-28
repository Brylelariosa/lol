#include "camera.h"
#include "entity.h"

void camera_follow(Camera* cam, const Entity* target, int screen_w, int screen_h) {
    cam->x = target->x - FX_FROM_INT(screen_w / 2) + FX_FROM_INT(target->w / 2);
    cam->y = target->y - FX_FROM_INT(screen_h / 2) + FX_FROM_INT(target->h / 2);
}

void camera_clamp(Camera* cam, int level_w_px, int level_h_px, int screen_w, int screen_h) {
    Fixed max_x = FX_FROM_INT(level_w_px - screen_w);
    Fixed max_y = FX_FROM_INT(level_h_px - screen_h);
    if (cam->x < 0) cam->x = 0;
    if (cam->x > max_x) cam->x = max_x;
    if (cam->y < 0) cam->y = 0;
    if (cam->y > max_y) cam->y = max_y;
}
