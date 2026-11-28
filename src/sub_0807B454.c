extern s32 applyAreaSpecialBehavior(void *, void *, void *);
extern void sub_0806D588(void *, void *);
extern void stepDelayTimer(void *, void *);
extern void releaseEntityIfOffscreen(void *, void *);
extern void sub_080C31E0(void *, s32);

struct GlobalState {
    u8 _0[0x10];
    u32 f0010;
    u8 _1[0x14E2 - 0x14];
    u16 f14E2;
    u32 f14E4;
    u8 _2[0x14ED - 0x14E8];
    u8 f14ED;
    u8 _3[0x173A - 0x14EE];
    u8 f173A;
    u8 _4[0x18C2 - 0x173B];
    u16 f18C2;
};
extern struct GlobalState gMainWorkspace;

/* Entity AI callback: update motion, copy a global value, then end or continue the action. */
void sub_0807B454(u8 *self) {
    u8 *actor;
    u8 *work;
    u8 *state;
    struct GlobalState *gs;
    actor = *(u8 **)(self + 0x6C);
    work = actor + 4;
    state = *(u8 **)(self + 0x38);
    if (applyAreaSpecialBehavior(self, state, work) > 0) {
        sub_080C31E0(self, *(s32 *)(self + 0x24));
        return;
    }
    gs = &gMainWorkspace;
    gs->f14E2 = 0x14D;
    gs->f14E4 = 0x0F;
    *(s32 *)(actor + 4) += *(s32 *)(work + 8);
    *(s32 *)(work + 4) += *(s32 *)(work + 0x0C);
    *(u16 *)state = gs->f18C2;
    stepDelayTimer(actor + 0x20, state);
    sub_0806D588(state, work);
    if (gs->f173A == 0x1C || (gs->f14ED == 0 && gs->f0010 != 0)) {
        sub_080C31E0(self, *(s32 *)(self + 0x24));
    } else {
        releaseEntityIfOffscreen(self, state);
    }
}
