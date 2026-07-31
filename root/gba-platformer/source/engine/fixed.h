#ifndef ENGINE_FIXED_H
#define ENGINE_FIXED_H

#include <stdint.h>

// Q8.8 fixed-point (8 bits of fraction). GBA has no FPU, so all game math
// uses this instead of float.
typedef int32_t Fixed;

#define FX_SHIFT 8
#define FX_ONE   (1 << FX_SHIFT)

#define FX_FROM_INT(n)    ((Fixed)((n) * FX_ONE))
#define FX_TO_INT(f)      ((int)((f) >> FX_SHIFT))
#define FX_FRAC(num, den) ((Fixed)(((int64_t)(num) << FX_SHIFT) / (den)))
#define FX_MUL(a, b)      ((Fixed)(((int64_t)(a) * (b)) >> FX_SHIFT))

#endif
