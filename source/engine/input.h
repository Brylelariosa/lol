#ifndef ENGINE_INPUT_H
#define ENGINE_INPUT_H

typedef enum {
    KEY_A      = 1 << 0,
    KEY_B      = 1 << 1,
    KEY_SELECT = 1 << 2,
    KEY_START  = 1 << 3,
    KEY_RIGHT  = 1 << 4,
    KEY_LEFT   = 1 << 5,
    KEY_UP     = 1 << 6,
    KEY_DOWN   = 1 << 7,
    KEY_R      = 1 << 8,
    KEY_L      = 1 << 9,
} InputKey;

// Call once per frame, before reading any key state.
void input_poll(void);

int input_is_down(InputKey key);       // held this frame
int input_was_pressed(InputKey key);   // went down this frame (edge)
int input_was_released(InputKey key);  // went up this frame (edge)

#endif
