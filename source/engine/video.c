#include "video.h"

static void video_oam_hide_all(void) {
    for (int i = 0; i < OAM_COUNT; i++) {
        OAM[i].attr0 = OBJ_HIDE;
        OAM[i].attr1 = 0;
        OAM[i].attr2 = 0;
    }
}

void video_init_mode0(void) {
    REG_DISPCNT = DCNT_MODE0 | DCNT_BG0 | DCNT_OBJ | DCNT_OBJ_1D;
    REG_BG0CNT  = BG_CBB(BG_CHAR_BASE) | BG_SBB(BG_SCREEN_BASE) | BG_4BPP | BG_SIZE_32x32;
    video_oam_hide_all();
}

void video_wait_vblank(void) {
    while (REG_VCOUNT >= 160) {}  // if already in vblank, wait for it to end first
    while (REG_VCOUNT < 160) {}   // then wait for the next vblank to start
}

void video_set_bg0_scroll(int x, int y) {
    REG_BG0HOFS = (uint16_t)x;
    REG_BG0VOFS = (uint16_t)y;
}

static void write_solid_tile(uint32_t char_base_addr, int tile_index, uint8_t color_index) {
    volatile uint32_t* tile = (volatile uint32_t*)(char_base_addr + (uint32_t)tile_index * 32);
    uint32_t px = color_index & 0xF;
    uint32_t word = px | (px << 4) | (px << 8) | (px << 12)
                  | (px << 16) | (px << 20) | (px << 24) | (px << 28);
    for (int i = 0; i < 8; i++) {
        tile[i] = word;
    }
}

void video_upload_bg_tile(int tile_index, uint8_t color_index) {
    write_solid_tile(0x06000000, tile_index, color_index);
}

void video_upload_obj_tile(int tile_index, uint8_t color_index) {
    write_solid_tile(OBJ_CHAR_BASE, tile_index, color_index);
}

void video_upload_bg_map(const uint16_t* tiles, int w, int h) {
    volatile uint16_t* map = (volatile uint16_t*)(0x06000000 + (uint32_t)BG_SCREEN_BASE * 0x800);
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            map[y * 32 + x] = tiles[y * w + x];
        }
    }
}

void video_set_bg_palette(int index, uint16_t color) {
    BG_PALETTE[index] = color;
}

void video_set_obj_palette(int index, uint16_t color) {
    OBJ_PALETTE[index] = color;
}

void video_oam_set(int slot, int x, int y, int tile_index, int hflip, int palette) {
    OAM[slot].attr0 = ((uint16_t)y & 0xFF) | OBJ_SHAPE_SQUARE;
    OAM[slot].attr1 = ((uint16_t)x & 0x1FF) | OBJ_SIZE_8 | (hflip ? OBJ_HFLIP : 0);
    OAM[slot].attr2 = ((uint16_t)tile_index & 0x3FF) | (((uint16_t)palette & 0xF) << 12);
}

void video_oam_hide(int slot) {
    OAM[slot].attr0 |= OBJ_HIDE;
}
