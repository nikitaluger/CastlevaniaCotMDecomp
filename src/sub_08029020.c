extern s32 sub_0800583C(s32);
extern void setAnimationFrame(s32, void *, s32, s32);
extern s32 sub_080C364C(s32, s32);
extern s32 sub_080C31E0(s32, s32);
extern void sub_080C31E4(void *, void *, s32);
extern s32 D_08671BFC;
extern s32 gMainObjTimerCallback;
extern u8 D_0866DA10[];

/* Drive a scripted sway: set anim frame 0, derive a sine-like vertical offset
 * from the step's angle through the phase callback, store it as the object's Y,
 * then reset the angle after 0x50 ticks. */
void sub_08029020(void *obj) {
    u8 *data = (u8 *)obj;
    s32 gfx = *(s32 *)(data + 0x38);
    u8 *state = *(u8 **)(data + 0x3C);
    u8 *anim = state + 0x34;
    u8 *control = state + 0x48;
    s32 *phaseCallback;
    s32 phase;

    setAnimationFrame(gfx, anim, 0, 1);
    phaseCallback = &D_08671BFC;
    phase = sub_080C364C(*(s32 *)(control + 8) << 16, 0x50);
    *(s32 *)(state + 0xC) = *(s32 *)(control + 4) + (sub_080C31E0(phase + 0x4000, *phaseCallback) << 4);
    if ((*(s32 *)(state + 0x50))++ > 0x50) {
        *(s32 *)(control + 8) = 0;
    }
}
