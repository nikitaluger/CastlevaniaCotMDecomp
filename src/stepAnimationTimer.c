extern void setAnimationFrame(s32, s32, s16, s32);
extern void randomizeAnimationDelay(void *, u8, u8);

struct S_8056B58 {
    u8 frame;
    s8 lastFrame;
    u8 ticks;
    u8 ticksReload;
    s16 *durations;
};

/* Timed animation step: count the current frame down; on expiry advance to the
 * next frame (wrapping to 0 and re-randomizing the frame delay between minDelay
 * and maxDelay), then play that frame's animation with its duration. */
void stepAnimationTimer(s32 arg0, s32 arg1, struct S_8056B58 *anim, u8 minDelay, u8 maxDelay)
{
    anim->ticks -= 1;
    if (anim->ticks == 0) {
        anim->ticks = anim->ticksReload;
        anim->frame += 1;
        if ((s8)anim->frame == anim->lastFrame) {
            anim->frame = 0;
            randomizeAnimationDelay(anim, minDelay, maxDelay);
        }
        setAnimationFrame(arg0, arg1, anim->durations[(s8)anim->frame], 1);
    }
}
