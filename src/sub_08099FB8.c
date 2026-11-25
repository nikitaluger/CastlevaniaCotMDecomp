extern void sub_08005E80(s32);
extern void sub_080114DC(s32, void *, s32, s32);
extern void sub_08011EE8(void *, s32, s32);
extern void sub_0809C4E0(s32, s32);
extern void sub_080C31E4(void *, void *, s32);
struct S_02025FF0_1754 { u8 _0[0x1754]; s32 v; };
extern struct S_02025FF0_1754 D_02025FF0;

/* Advances the actor's movement; when its action flag is set, clamps a global
 * timer upward, plays a cue, starts an animation, clears a part field, and
 * advances the script step. */
void sub_08099FB8(void *arg0) {
    u8 *self = (u8 *)arg0;
    s32 sprite = *(s32 *)(self + 0x38);
    u8 *work = *(u8 **)(self + 0x3C);
    u8 *animState = work + 0x34;
    u8 *parts = work + 0x48;
    s32 *scriptCb;
    sub_08011EE8(work, 0x2D82, 0);
    if (*(u16 *)(work + 2) & 4) {
        if (D_02025FF0.v <= 0x10) D_02025FF0.v = 0x11;
        sub_08005E80(0x167);
        sub_080114DC(sprite, animState, 0xF, 0);
        sub_0809C4E0(*(s32 *)(parts + 8), 0);
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
        scriptCb = (s32 *)0x08671BB0;
        sub_080C31E4(self + 0x18, self + 0x22, *scriptCb);
    }
}
