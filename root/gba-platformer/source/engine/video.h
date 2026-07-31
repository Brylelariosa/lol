#ifndef ENGINE_VIDEO_H
#define ENGINE_VIDEO_H

#include <stdint.h>

// This module is the ONLY place in the codebase that touches raw GBA
// hardware registers/memory. Game code never pokes VRAM/OAM directly -
// it goes through these functions. Keeps hardware details isolated and
// swappable (e.g. if you later add libtonc/libgba, only this file changes).

#define SCREEN_W 240
#define SCREEN_H 160

// --- Display control ---
#define REG_DISPCNT  (*(volatile uint32_t*)0x04000000)
#define REG_VCOUNT   (*(volatile uint16_t*)0x04000006)
#define REG_BG0CNT   (*(volatile uint16_t*)0x04000008)
#define REG_BG0HOFS  (*(volatile uint16_t*)0x04000010)
#define REG_BG0VOFS  (*(volatile uint16_t*)0x04000012)

#define DCNT_MODE0    0x0000
#define DCNT_BG0      0x0100
#define DCNT_OBJ      0x1000
#define DCNT_OBJ_1D   0x0040

#define BG_CBB(n)      ((n) << 2)   // character base block (16KB units)
#define BG_SBB(n)      ((n) << 8)   // screen base block (2KB units)
#define BG_4BPP        (0 << 7)
#define BG_SIZE_32x32  (0 << 14)

#define BG_CHAR_BASE   0    // BG tiles at 0x06000000
#define BG_SCREEN_BASE 8    // BG tilemap at 0x06004000 (clear of char block 0)
#define OBJ_CHAR_BASE  0x06010000  // sprite tiles always start here

#define BG_PALETTE   ((volatile uint16_t*)0x05000000)
#define OBJ_PALETTE  ((volatile uint16_t*)0x05000200)
#define RGB15(r, g, b) ((uint16_t)((r) | ((g) << 5) | ((b) << 10)))

// --- OAM / sprites ---
typedef struct {
    uint16_t attr0;
    uint16_t attr1;
    uint16_t attr2;
    int16_t  affine_pad;
} OamEntry;

#define OAM        ((volatile OamEntry*)0x07000000)
#define OAM_COUNT  128

#define OBJ_SHAPE_SQUARE (0 << 14)
#define OBJ_SIZE_8       (0 << 14)
#define OBJ_HFLIP        (1 << 12)
#define OBJ_HIDE         (1 << 9)

void video_init_mode0(void);
void video_wait_vblank(void);
void video_set_bg0_scroll(int x, int y);

// Fills an 8x8 4bpp tile with a single solid palette color index.
// Good enough for placeholder art; swap for grit-converted PNGs later.
void video_upload_bg_tile(int tile_index, uint8_t color_index);
void video_upload_obj_tile(int tile_index, uint8_t color_index);

void video_upload_bg_map(const uint16_t* tiles, int w, int h);

void video_set_bg_palette(int index, uint16_t color);
void video_set_obj_palette(int index, uint16_t color);

void video_oam_set(int slot, int x, int y, int tile_index, int hflip, int palette);
void video_oam_hide(int slot);

#endif
