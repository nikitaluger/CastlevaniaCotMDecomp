extern s32 sub_0806D450(void *, void *, void *);
extern s32 sub_0806D588(void *, void *);
extern void sub_080C31E4(void *, void *, s32);
extern void sub_080C31E0(void *, s32);
struct S_02025FF0_x {
    u8 _0[0x10]; s32 v10;
    u8 _14[0x14ED - 0x14]; u8 v14ED;
    u8 _14EE[0x14FC - 0x14EE]; s32 v14FC;
    u8 _1500[0x173A - 0x1500]; u8 v173A;
};
extern struct S_02025FF0_x gMainWorkspace;
struct T8 { u8 pad[4]; s32 val; };
extern struct T8 D_080E00E8[];

/* Timed script step: apply any special area behavior, snap the actor's position
 * to the grid, run a countdown reloaded from a table, and end the script when
 * the timer expires or a global state demands it. */
void sub_08070BD0(void *arg0) {
    u8 *self = (u8 *)arg0;
    u8 *pos = (*(u8 **)(self + 0x6C)) + 4;
    u8 *actor = *(u8 **)(self + 0x38);
    s32 *tablePtr;
    s32 countdown;
    if (sub_0806D450(self, actor, pos) > 0) {
        sub_080C31E0(arg0, *(s32 *)((u8 *)arg0 + 0x24));
        return;
    }
    sub_0806D588(actor, pos);
    countdown = *(s32 *)(pos + 0x5C) - 1;
    *(s32 *)(pos + 0x5C) = countdown;
    if (countdown == 0) {
        *(s32 *)(pos + 0x5C) = D_080E00E8[*(s32 *)(pos + 0x60)].val;
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
        tablePtr = (s32 *)0x08671BB0;
        sub_080C31E4(self + 0x18, self + 0x22, *tablePtr);
    }
    if (gMainWorkspace.v14FC != 0) {
        sub_080C31E0(arg0, *(s32 *)((u8 *)arg0 + 0x24));
    } else if (gMainWorkspace.v173A == 0x1C || (gMainWorkspace.v14ED == 0 && gMainWorkspace.v10 != 0)) {
        sub_080C31E0(arg0, *(s32 *)((u8 *)arg0 + 0x24));
    }
}
