/* Layout of the global scene state (gMainWorkspace) used by entity-component updates:
 * f10    - nonzero while a scene transition is active
 * f14ED  - room flag; zero enables the transition-flag check
 * f173A  - scene id; 0x1C forces the entity's default callback
 * f18C2  - state word copied into an entity's animation component */
struct SceneStateFF0 {
    u8 _0[0x10];
    s32 f10;
    u8 _1[0x14ED - 0x14];
    u8 f14ED;
    u8 _2[0x173A - 0x14EE];
    u8 f173A;
    u8 _3[0x18C2 - 0x173B];
    u16 f18C2;
};
extern struct SceneStateFF0 gMainWorkspace;

extern s32 stepDelayTimer(void *, u16 *);
extern s32 cullOffscreenEntity(void *, u16 *);
extern s32 checkGlobalStateChange(void *, u16 *, void *);
extern s32 sub_0806D588(u16 *, void *);
extern void _call_via_r1(void *, s32);

/* Advance a timed entity component: integrate its angle and position, copy the
 * scene state word into its sprite, count down its lifetime, and destroy the
 * entity when the timer expires or global scene flags require it. */
void sub_080797D8(u8 *entity) {
    void *self;
    void *component;
    u8 *motion;
    u16 *state;

    component = *(void **)(entity + 0x6C);
    motion = (u8 *)component + 4;
    state = *(u16 **)(entity + 0x38);
    if (checkGlobalStateChange(entity, state, motion) == 0) {
        self = entity;
        *(s32 *)(motion + 0x0C) += 0x100;
        *(s32 *)((u8 *)component + 0x04) += *(s32 *)(motion + 0x08);
        *(s32 *)(motion + 0x04) += *(s32 *)(motion + 0x0C);
        *state = gMainWorkspace.f18C2;
        *(s32 *)(motion + 0x48) -= 1;
        if (*(s32 *)(motion + 0x48) == 0 ||
            (stepDelayTimer((u8 *)component + 0x20, state), sub_0806D588(state, motion), gMainWorkspace.f173A == 0x1C) ||
            (gMainWorkspace.f14ED == 0 && gMainWorkspace.f10 != 0)) {
            _call_via_r1(self, *(s32 *)((u8 *)self + 0x24));
            return;
        }
        cullOffscreenEntity(self, state);
    }
}
