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

/* Update a short-lived effect that tracks its owner: bail out on global
 * despawn flags, advance two 16-bit timers, copy the owner's world position
 * into screen space, then despawn on state change, timer wrap or off-screen. */
void sub_08077E18(u8 *entity) {
    u8 *owner;
    u8 *ownerPos;
    u8 *fxState;
    struct S_02025FF0 *gs;
    owner = *(u8 **)(entity + 0x6C);
    ownerPos = owner + 4;
    fxState = *(u8 **)(entity + 0x38);
    if (checkGlobalStateChange(entity, fxState, ownerPos) != 0) return;
    {
        u32 timer = *(u16 *)(fxState + 4) + 0x40;
        *(u16 *)(fxState + 4) = timer;
        *(u16 *)(fxState + 6) = *(u16 *)(fxState + 6) + 0x40;
        if ((s32)(timer << 16) > 0x03FF0000) {
            _call_via_r1(entity, *(s32 *)(entity + 0x24));
            return;
        }
    }
    gs = &gMainWorkspace;
    { u16 initial = gMainWorkspace.f18C2; *(u16 *)fxState = initial; }
    stepDelayTimer(owner + 0x20, fxState);
    sub_0806D588(fxState, ownerPos);
    if (gs->f173A == 0x1C || (gs->f14ED == 0 && gs->f10 != 0)) {
        _call_via_r1(entity, *(s32 *)(entity + 0x24));
    } else {
        cullOffscreenEntity(entity, fxState);
    }
}
