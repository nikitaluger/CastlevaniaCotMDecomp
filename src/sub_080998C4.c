struct GameTimer { u8 _0[0x1754]; s32 timer; };
extern struct GameTimer gMainWorkspace;

extern void sub_08005E80(s32);
extern void setObjectAnimation(void *, void *, s32, s32);
extern void sub_0809C4E0(s32, s32);
extern void sub_080C31E4(void *, void *, s32);

/* Start the actor's scripted action: clamp the global timer upward (minimum
 * 0x11), play cue 0x167, start animation 0xF, clear the part field, then clear
 * the current script byte and advance the script step. */
void sub_080998C4(void *arg0) {
    u8 *self = (u8 *)arg0;
    void *sprite = *(void **)(self + 0x38);
    u8 *work = *(u8 **)(self + 0x3C);
    u8 *animState = work + 0x34;
    u8 *parts = work + 0x48;
    if (gMainWorkspace.timer <= 0x10) {
        gMainWorkspace.timer = 0x11;
    }
    sub_08005E80(0x167);
    setObjectAnimation(sprite, animState, 0x0F, 0);
    sub_0809C4E0(*(s32 *)(parts + 8), 0);
    *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
    {
        s32 *scriptCb = (s32 *)0x08671BB0;
        sub_080C31E4(self + 0x18, self + 0x22, *scriptCb);
    }
}
