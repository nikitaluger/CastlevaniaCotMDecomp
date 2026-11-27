void setAnimationFrame(s32, s32, s32, s32);
void stepAnimationTrack(s32, s32);
void sub_080C31E4(void *, void *, s32);

/* Switches the actor to animation 2, refreshes the animator and, once its
 * status byte reports completion (bit 1), clears the script action byte and
 * dispatches the next handler. */
void sub_080B818C(void *entity) {
    s32 animState;
    s32 sprite;
    void *work;
    s32 *scriptCb;

    sprite = *(s32 *)((u8 *)entity + 0x38);
    work = *(void **)((u8 *)entity + 0x3C);
    animState = (s32)work + 0x34;
    setAnimationFrame(sprite, animState, 2, 0);
    stepAnimationTrack(sprite, animState);
    if (2 & *(u8 *)((u8 *)work + 0x34)) {
        *(s8 *)((s8 *)((*(s16 *)((u8 *)entity + 0x22) * 2) + entity) + 0x19) = 0;
        scriptCb = (s32 *)0x08671BB0;
        sub_080C31E4((u8 *)entity + 0x18, (u8 *)entity + 0x22, *scriptCb);
    }
}
