extern s32 sub_08005910(s32, s32);
extern void forceAnimationFrame(s32, void *, s32, s32);
extern void sub_08011528(s32, void *);
extern void sub_0809856C(s32, void *, s32);
extern void sub_080C31E4(void *, void *, s32);

struct S_02025FF0_174C { u8 pad[0x174C]; u32 targetX; u32 targetY; };
extern struct S_02025FF0_174C gMainWorkspace;

/* Entity update: periodically plays sound 0x17A, advances the actor's
 * animation, and in state 0x18 stores at actor+0x48 the angle from the actor
 * (actor+8/+0xC) toward the current target (gMainWorkspace) before moving to the
 * next state.  sub_08005910 is atan2(deltaY, deltaX). */
void sub_080AE3D0(u8 *self) {
    s32 gfx = *(s32 *)(self + 0x38);
    u8 *actor = *(u8 **)(self + 0x3C);
    u8 *anim = actor + 0x34;
    s32 deltaY, deltaX;
    s32 angle;
    s32 *funcSlot;

    sub_0809856C(0xBD << 1, actor + 0x50, 0xF);
    sub_08011528(gfx, anim);
    if (*(u8 *)anim & 2) {
        forceAnimationFrame(gfx, anim, 0x47, 0);
    }
    if (*(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) == 0x18) {
        deltaY = gMainWorkspace.targetY - *(s32 *)(actor + 0xC);
        deltaX = gMainWorkspace.targetX - *(s32 *)(actor + 8);
        angle = sub_08005910(deltaY, deltaX);
        *(s32 *)(actor + 0x48) = angle;
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
        funcSlot = (s32 *)0x08671BB0;
        sub_080C31E4(self + 0x18, self + 0x22, *funcSlot);
    }
}
