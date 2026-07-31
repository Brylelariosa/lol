#ifndef GAME_CAMERA_H
#define GAME_CAMERA_H

#include "../engine/fixed.h"

typedef struct Camera {
    Fixed x, y;
} Camera;

struct Entity; // forward decl, avoids pulling in entity.h just for this signature

void camera_follow(Camera* cam, const struct Entity* target, int screen_w, int screen_h);
void camera_clamp(Camera* cam, int level_w_px, int level_h_px, int screen_w, int screen_h);

#endif
