extern u32 gMainWorkspace[];

void stepDelayTimer(void *, void *);
void startEffectTimer(void *, u32, u32);
void sub_0806D588(void *, void *);
void sub_080C31E4(void *, void *, u32);

/* Actor step while the global state gMainWorkspace[7] is 1: start animation set
 * 0x0850436C (advancing the script), then tick the animation and copy the
 * mover's position to the sprite. */
void sub_08089EF4(void *arg0) {
    u8 *self = (u8*)arg0;
    u8 *mover = *(u8 **)(self + 0x6C);
    u8 *pos = mover + 4;
    u8 *sprite = *(u8 **)(self + 0x38);
    u32 *callback;
    if (gMainWorkspace[7] == 1) {
        startEffectTimer(mover + 0x20, 0, 0x0850436C);
        *(u8*)(self + *(s16*)(self + 0x22) * 2 + 0x19) = 0;
        callback = (u32*)0x08671BB0;
        sub_080C31E4(self + 0x18, self + 0x22, *callback);
    }
    stepDelayTimer(mover + 0x20, sprite);
    sub_0806D588(sprite, pos);
}
