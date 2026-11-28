extern s32 getAngleFromDelta(s32, s32);
extern s32 getAngleTurnDirection(s32, s32);
extern void sub_080B5ACC(void *);
extern void sub_080C31E4(void *, void *, s32);

struct S_02025FF0_1750 { u8 _0[0x174C]; s32 f174C; s32 f1750; };
extern struct S_02025FF0_1750 gMainWorkspace;

/* Steers an object toward the player by a one-step angle change, advances its
 * animation timer, and triggers the stored effect on frame 0xF0. */
void sub_080B5A5C(void *obj) {
    u8 *self = (u8 *)obj;
    u8 *target = *(u8 **)(self + 0x3C);
    s32 heading = *(s32 *)(self + 0x7C);
    s32 deltaX = gMainWorkspace.f1750 - *(s32 *)(target + 0x0C);
    s32 deltaY = gMainWorkspace.f174C - *(s32 *)(target + 0x08);
    s32 targetAngle = getAngleFromDelta(deltaX, deltaY);
    s32 turnStep = getAngleTurnDirection(heading, targetAngle);

    *(s32 *)(self + 0x7C) = *(s32 *)(self + 0x7C) + (turnStep << 8);
    sub_080B5ACC(obj);

    if (*(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) == 0xF0) {
        s32 *lit;
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
        lit = (s32 *)0x08671BB0;
        sub_080C31E4(self + 0x18, self + 0x22, *lit);
    }
}
