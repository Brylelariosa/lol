#include "input.h"
#include <stdint.h>

#define REG_KEYINPUT (*(volatile uint16_t*)0x04000130)

// REG_KEYINPUT is active-low (0 = pressed), so we invert into "active-high"
// values internally and expose a normal is-down/pressed/released API.
static uint16_t s_current  = 0;
static uint16_t s_previous = 0;

void input_poll(void) {
    s_previous = s_current;
    s_current  = (uint16_t)(~REG_KEYINPUT);
}

int input_is_down(InputKey key) {
    return (s_current & key) != 0;
}

int input_was_pressed(InputKey key) {
    return (s_current & key) && !(s_previous & key);
}

int input_was_released(InputKey key) {
    return !(s_current & key) && (s_previous & key);
}
