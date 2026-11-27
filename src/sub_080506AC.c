void setAnimationFrame(void *, void *, s32, s32);
void sub_080C31E4(void *, void *, s32);
extern s32 gMainObjTimerCallbacks;

/* Play sprite animation 0x0E on the entity (animation state at work+0x34); if
 * the animation's finished flag (bit 1 of its state byte) is set, clear the
 * current step's timer and run the next command-script handler. */
void sub_080506AC(void *arg0) {
    void *sprite = *(void **)((u8 *)arg0 + 0x38);
    u8 *work = *(u8 **)((u8 *)arg0 + 0x3C);
    u8 *anim = work + 0x34;
    s32 *scriptTable;
    setAnimationFrame(sprite, anim, 0xE, 0);
    if (2 & *anim) {
        *(u8 *)((u8 *)((u32)(*(s16 *)((u8 *)arg0 + 0x22)) * 2 + (u32)arg0) + 0x19) = 0;
        scriptTable = &gMainObjTimerCallbacks;
        sub_080C31E4((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, *scriptTable);
    }
}
