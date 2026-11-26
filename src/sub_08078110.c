extern s32 sub_0806D518(void *, void *, void *);
extern s32 sub_08007DD8(u32, s32, s32);
extern void sub_08003A6C(void *, s32, u32);
extern void sub_08003740(void *, void *);
extern void sub_0806D330(void *, void *);
extern void sub_0806D588(void *, void *);
extern void sub_080C31E0(void *, s32);
extern void sub_080C31E4(void *, void *, s32);
extern void sub_08005E80(s32);
struct S_02025FF0 {
    u8 _0[0x10];
    s32 f10;
    u8 _14[0x14ED-0x14];
    u8 f14ED;
    u8 _14EE[0x173A-0x14EE];
    u8 f173A;
    u8 _173B[0x1754-0x173B];
    s32 f1754;
    u8 _1758[0x18A8-0x1758];
    u8 f18A8;
    u8 _18A9[0x19];
    u16 f18C2;
};
extern struct S_02025FF0 gMainWorkspace;
extern u32 gMainObjTimerCallback;

static inline u32 bitOne(u16 v) {
    u32 m = 1;
    m &= v;
    return m;
}

/* One step of an entity's scripted motion: advance/clamp its phase, spawn and
 * announce an event when the phase or world-position test fires, refresh the
 * attached sprite, then dispatch the next callback. */
void sub_08078110(u8 *obj) {
    void *self;
    void *script;
    void *stateBase;
    void *sprite;
    void *motion;
    u32 *callbackTbl;
    s32 phaseSum;
    u8 zero;
    self = obj;
    script = *(void **)((u8 *)self + 0x6C);
    stateBase = (u8 *)script + 4;
    sprite = *(void **)((u8 *)self + 0x38);
    motion = stateBase;
    if (sub_0806D518(self, sprite, motion) != 0) return;
    *(s32 *)((u8 *)motion + 0x0C) += 0x4000;
    if (*(s32 *)((u8 *)motion + 0x0C) > 0x80000) *(s32 *)((u8 *)motion + 0x0C) = 0x80000;
    *(s32 *)((u8 *)script + 4) += *(s32 *)((u8 *)motion + 8);
    phaseSum = *(s32 *)((u8 *)motion + 4) + *(s32 *)((u8 *)motion + 0x0C);
    *(s32 *)((u8 *)motion + 4) = phaseSum;
    if (bitOne(*(u16 *)(*(void **)((u8 *)motion + 0x2C) + 0x14)) != 0 ||
        (sub_08007DD8(((u32)gMainWorkspace.f18A8 << 6) + 0x02023130, *(s32 *)((u8 *)script + 4), phaseSum) << 16) != 0) {
        if (gMainWorkspace.f1754 <= 8) gMainWorkspace.f1754 = 9;
        sub_08003A6C((u8 *)script + 0x20, 0, 0x084D8DF4);
        *(u16 *)(*(void **)((u8 *)motion + 0x2C) + 0x06) = (zero = 0, 8);
        *(u16 *)(*(void **)((u8 *)motion + 0x2C) + 0x08) = 8;
        sub_08005E80(0x142);
        *(u8 *)((u8 *)self + (*(s16 *)((u8 *)self + 0x22) * 2) + 0x19) = zero;
        callbackTbl = &gMainObjTimerCallback;
        sub_080C31E4((u8 *)self + 0x18, (u8 *)self + 0x22, *callbackTbl);
    }
    *(u16 *)sprite = gMainWorkspace.f18C2;
    sub_08003740((u8 *)stateBase + 0x1C, sprite);
    sub_0806D588(sprite, motion);
    if (gMainWorkspace.f173A == 0x1C || (gMainWorkspace.f14ED == 0 && gMainWorkspace.f10 != 0)) {
        sub_080C31E0(self, *(s32 *)((u8 *)self + 0x24));
        return;
    }
    sub_0806D330(self, sprite);
}
