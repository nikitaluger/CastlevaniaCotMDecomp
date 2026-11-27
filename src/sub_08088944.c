extern u32 gMainWorkspace[];
struct S_02025FF0_14B8 { u8 _0[0x14B8]; u32 activeFlag; };
extern struct S_02025FF0_14B8 D_02025FF0_14B8;
s32 stepDelayTimer(void *, void *);
void sub_0806D588(void *, void *);
void sub_080C31E4(void *, void *, u32);
void sub_080C31E0(void *, void *);
void startEffectTimer(void *, u32, u32);

/* Actor step: when the mover has finished (stepDelayTimer returns 0), set global
 * state gMainWorkspace[7] to 2, clear the script step byte and advance. */
void sub_080888F4(void *arg0) {
    u8 *self = (u8*)arg0;
    u8 *mover = *(u8 **)(self + 0x6C);
    u8 *pos = mover + 4;
    u8 *sprite = *(u8 **)(self + 0x38);
    u32 *callback;
    s32 result = stepDelayTimer(mover + 0x20, sprite);
    if (result == 0) {
        gMainWorkspace[7] = 2;
        *(u8*)(self + *(s16*)(self + 0x22) * 2 + 0x19) = result;
        callback = (u32*)0x08671BB0;
        sub_080C31E4(self + 0x18, self + 0x22, *callback);
    }
    sub_0806D588(sprite, pos);
}

/* Actor step while the global state is 0x0E: start animation set 0x08500D8C
 * (advancing the script), then tick the animation and copy the mover's
 * position to the sprite. */
void sub_08088944(void *arg0) {
    u8 *self = (u8*)arg0;
    u8 *mover = *(u8 **)(self + 0x6C);
    u8 *pos = mover + 4;
    u8 *sprite = *(u8 **)(self + 0x38);
    u32 *callback;
    if (gMainWorkspace[5] == 0xE) {
        startEffectTimer(mover + 0x20, 0, 0x08500D8C);
        *(u8*)(self + *(s16*)(self + 0x22) * 2 + 0x19) = 0;
        callback = (u32*)0x08671BB0;
        sub_080C31E4(self + 0x18, self + 0x22, *callback);
    }
    stepDelayTimer(mover + 0x20, sprite);
    sub_0806D588(sprite, pos);
}

/* Actor step while the global state is 0x0A: start animation set 0x08500D3C
 * (advancing the script), then tick the animation and copy the mover's
 * position to the sprite. */
void sub_08088894(void *arg0) {
    u8 *self = (u8*)arg0;
    u8 *mover = *(u8 **)(self + 0x6C);
    u8 *pos = mover + 4;
    u8 *sprite = *(u8 **)(self + 0x38);
    u32 *callback;
    if (gMainWorkspace[5] == 0xA) {
        startEffectTimer(mover + 0x20, 0, 0x08500D3C);
        *(u8*)(self + *(s16*)(self + 0x22) * 2 + 0x19) = 0;
        callback = (u32*)0x08671BB0;
        sub_080C31E4(self + 0x18, self + 0x22, *callback);
    }
    stepDelayTimer(mover + 0x20, sprite);
    sub_0806D588(sprite, pos);
}

/* Actor step: while the +0x14B8 global flag is set, dispatch the entity's
 * handler at +0x24; otherwise copy the mover's position to the sprite. */
void sub_080889F4(void *arg0) {
    u8 *self = (u8*)arg0;
    u8 *pos = *(u8 **)(self + 0x6C) + 4;
    u8 *sprite = *(u8 **)(self + 0x38);
    if (D_02025FF0_14B8.activeFlag != 0) {
        sub_080C31E0(self, *(void **)(self + 0x24));
    } else {
        sub_0806D588(sprite, pos);
    }
}
