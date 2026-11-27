struct S_02025FF0 {
    u8 _0[0x10];
    s32 f10;
    u8 _1[0x14ED - 0x14];
    u8 f14ED;
    u8 _2[0x173A - 0x14EE];
    u8 f173A;
    u8 _3[0x18C2 - 0x173B];
    u16 f18C2;
};
extern struct S_02025FF0 gMainWorkspace;
extern s32 checkGlobalStateChange(void *, void *, void *);
extern s32 stepDelayTimer(void *, void *);
extern void cullOffscreenEntity(void *, void *);
extern void sub_0806D588(void *, void *);
extern void _call_via_r1(void *, s32);

/* Advances an entity's angle counters and integrates its motion, copies the
 * global state word into it, steps its timer and snaps it to the grid; the
 * entity is destroyed on certain global states or when it leaves the level. */
void sub_08079068(u8 *entity) {
    u8 *component;
    u8 *motion;
    u8 *state;
    struct S_02025FF0 *dp;
    component = *(u8 **)(entity + 0x6C);
    motion = component + 4;
    state = *(u8 **)(entity + 0x38);
    if (checkGlobalStateChange(entity, state, motion) != 0) return;
    {
        u32 angle = *(u16 *)(state + 4) + 0x40;
        *(u16 *)(state + 4) = angle;
        *(u16 *)(state + 6) = *(u16 *)(state + 6) + 0x40;
        if ((s32)(angle << 16) > 0x03FF0000) {
            _call_via_r1(entity, *(s32 *)(entity + 0x24));
            return;
        }
    }
    *(s32 *)(component + 4) = *(s32 *)(component + 4) + *(s32 *)(motion + 8);
    *(s32 *)(motion + 4) = *(s32 *)(motion + 4) + *(s32 *)(motion + 0x0C);
    dp = &gMainWorkspace;
    { u16 stateWord = gMainWorkspace.f18C2; *(u16 *)state = stateWord; }
    stepDelayTimer(component + 0x20, state);
    sub_0806D588(state, motion);
    if (dp->f173A == 0x1C || (dp->f14ED == 0 && dp->f10 != 0)) {
        _call_via_r1(entity, *(s32 *)(entity + 0x24));
    } else {
        cullOffscreenEntity(entity, state);
    }
}
