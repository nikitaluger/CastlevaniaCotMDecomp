extern void stepAnimationTrack(u32, u8 *);
extern void (*gScriptStepCallbacks)(void *, void *, s32);

/* Plays the entity's current animation frame; whenever the animation ends
 * (animator flag bit 1) it bumps the part's frame counter and restarts the
 * script step with argument 2 on odd frames and 0 on even ones. */
void sub_080343AC(u8 *arg0)
{
    u32 sprite;
    u8 *work;
    u8 *animator;
    u8 *part;
    s16 stepIndex;

    sprite = *(u32 *)(arg0 + 0x38);
    work = *(u8 **)(arg0 + 0x3C);
    animator = work + 0x34;
    part = work + 0x48;

    stepAnimationTrack(sprite, animator);

    if ((animator[0] & 2) != 0) {
        part[0x10]++;
        if (part[0x10] & 1) {
            stepIndex = *(s16 *)(arg0 + 0x22);
            arg0[stepIndex * 2 + 0x19] = 0;
            gScriptStepCallbacks(arg0 + 0x18, arg0 + 0x22, 2);
        } else {
            stepIndex = *(s16 *)(arg0 + 0x22);
            arg0[stepIndex * 2 + 0x19] = 0;
            gScriptStepCallbacks(arg0 + 0x18, arg0 + 0x22, 0);
        }
    }
}
