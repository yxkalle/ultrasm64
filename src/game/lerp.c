#include <ultra64.h>
#include "types.h"
#include "game_init.h"
#include "engine/math_util.h"
#include "camera.h"

#define LERP_THRESHOLD 400.0f
#define LERP_THRESHOLD_ANGLE 0x2000

static f32 localLerp(f32 current, f32 target, f32 multiplier) {
    current = current + (target - current) * multiplier;
    return current;
}

s32 abs_angle_diff(s16 x0, s16 x1) {
    s16 diff = x1 - x0;

    if (diff == -0x8000) {
        diff = -0x7FFF;
    }

    if (diff < 0) {
        diff = -diff;
    }

    return diff;
}

void warp_node(struct Object *node) {
    node->header.gfx.bothMats++;
    vec3f_copy(node->header.gfx.posLerp, node->header.gfx.pos);
    vec3s_copy(node->header.gfx.angleLerp, node->header.gfx.angle);
    vec3f_copy(node->header.gfx.scaleLerp, node->header.gfx.scale);
}

s32 approach_angle_lerp(s32 current, s32 target) {
    if (abs_angle_diff(current, target) >= 0x2000) {
        return target;
    }
    return target - localLerp((s16) (target - current), 0, gLerpSpeed);
}

f32 approach_pos_lerp(f32 current, f32 target) {
    if (ABS(target - current) >= LERP_THRESHOLD) {
        return target;
    }
    return localLerp(current, target, gLerpSpeed);
}
