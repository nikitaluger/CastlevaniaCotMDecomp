extern s32 stepDelayTimer(s32, u16 *);
extern s32 applyAreaSpecialBehavior(void *, u16 *, u8 *);
extern s32 sub_0806D588(u16 *, u8 *);
extern void sub_080C31E0(void *, s32);
struct S_02025FF0_x {
    u8 _0[0x10];
    s32 v10;
    u8 _14[0x14ED - 0x14];
    u8 v14ED;
    u8 _14EE[0x173A - 0x14EE];
    u8 v173A;
    u8 _173B[0x18C2 - 0x173B];
    u16 v18C2;
};
extern struct S_02025FF0_x gMainWorkspace;

/* Poll the actor's special behavior and timer: copy/derive its result, snap it to the grid, and end the state via callback when done. */
void sub_08083B50(void *arg0) {
    u8 *self = (u8 *)arg0;
    s32 actor = *(s32 *)(self + 0x6C);
    u8 *pos = (u8 *)(actor + 4);
    u16 *result = *(u16 **)(self + 0x38);
    if (applyAreaSpecialBehavior(arg0, result, pos) > 0) {
        sub_080C31E0(arg0, *(s32 *)(self + 0x24));
        return;
    }
    {
        u8 *src = *(u8 **)(pos + 0x4C);
        if (*(u8 *)(src + 1) == *(u8 *)(actor + 0x54)) {
            *(u32 *)(actor + 4) = *(u32 *)(src + 0xC);
            *(u32 *)(pos + 4) = *(u32 *)(src + 0x10);
        }
    }
    *result = gMainWorkspace.v18C2;
    if (stepDelayTimer(actor + 0x20, result) == 0) {
        sub_080C31E0(arg0, *(s32 *)(self + 0x24));
        return;
    }
    sub_0806D588(result, pos);
    if ((gMainWorkspace.v173A == 0x1C) || ((gMainWorkspace.v14ED == 0) && (gMainWorkspace.v10 != 0))) {
        sub_080C31E0(arg0, *(s32 *)(self + 0x24));
    }
}
