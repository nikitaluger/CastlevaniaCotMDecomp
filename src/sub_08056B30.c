extern void randomizeAnimationDelay(void *anim, u8 minDelay, u8 maxDelay);

struct S_8056B58 {
    u8 frame;
    s8 lastFrame;
    u8 ticks;
    u8 ticksReload;
    s16 *durations;
};

/* Start an animation: begin one frame before frame 0, set the last frame, the
 * per-frame durations and a random reload delay in [minDelay, maxDelay). */
void sub_08056B30(struct S_8056B58 *anim, u8 lastFrame, s16 *durations, u8 minDelay, u8 maxDelay) {
    anim->ticks = 1;
    anim->frame = 0xFF;
    anim->lastFrame = lastFrame;
    anim->durations = durations;
    randomizeAnimationDelay(anim, minDelay, maxDelay);
}
