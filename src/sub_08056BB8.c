extern s32 sub_08005820(s32 range);

/* Timed animation state (shared with sub_08056B30/sub_08056B58):
 * frame +0, lastFrame +1, ticks +2, ticksReload +3, durations +4. */
struct AnimTimer {
    u8 frame;
    s8 lastFrame;
    u8 ticks;
    s8 ticksReload;
};

/* Set the animation's per-frame tick reload delay (byte at +3) to a
 * pseudorandom value in [lower, upper); sub_08005820(n) gives a value in [0, n). */
void sub_08056BB8(struct AnimTimer *anim, u8 upper, u8 lower) {
    u8 base = lower;
    anim->ticksReload = (s8)(base + sub_08005820(upper - base));
}
