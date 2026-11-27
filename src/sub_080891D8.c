void startEffectTimer(s32, s32, s32);
void stepDelayTimer(s32, s32);
void sub_080C31E4(void *, void *, s32);
void sub_0806D588(s32, s32);

struct S_02025FF0_891D8 { u8 _0[0x14]; s32 state; u8 _1[0x20]; s32 spriteRef; };
extern struct S_02025FF0_891D8 gMainWorkspace;

/* Actor step: remember the sprite's +0x14 word globally; while the global
 * state is 0x17 start animation set 0x08500D50, tick it, clear the script step
 * byte and advance, then copy the mover's position to the sprite. */
void sub_080891D8(void *arg0) {
    u8 *self = (u8 *)arg0;
    u8 *mover = *(u8 **)(self + 0x6C);
    u8 *pos = mover + 4;
    s32 sprite = *(s32 *)(self + 0x38);
    s32 *callback;
    gMainWorkspace.spriteRef = *(s32 *)(sprite + 0x14);
    if (gMainWorkspace.state == 0x17) {
        mover += 0x20;
        startEffectTimer((s32)mover, 0, (s32)0x08500D50);
        stepDelayTimer((s32)mover, sprite);
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
        callback = (s32 *)0x08671BB0;
        sub_080C31E4(self + 0x18, self + 0x22, *callback);
    }
    sub_0806D588(sprite, (s32)pos);
}
