extern void setAnimationFrame(s32, void *, s32, s32);
extern void sub_080C31E8(void *, void *, s32, s32);

/* Play animation 8 on the parent object; when the animation's status byte has
 * bit 1 set, set the state field to 150, clear one script byte and push the
 * script forward by one instruction (code 3). */
void sub_08021F84(void *arg0) {
    u8 *script = (u8 *)arg0;
    s32 parent = *(s32 *)(script + 0x38);
    u8 *motion = *(u8 **)(script + 0x3C);
    u8 *anim = motion + 0x34;
    u8 *state = motion + 0x48;
    s32 *advanceFunc;
    setAnimationFrame(parent, anim, 8, 0);
    if (*(u8 *)anim & 2) {
        s16 stepIndex;
        u8 zero = 0;
        *(u16 *)(state + 6) = 0x96;
        stepIndex = *(s16 *)(script + 0x22);
        *(u8 *)(script + stepIndex * 2 + 0x17) = zero;
        advanceFunc = (s32 *)0x08671BD8;
        sub_080C31E8(script + 0x18, script + 0x22, 3, *advanceFunc);
    }
}
