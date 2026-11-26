extern s32 sub_08005910(s32 dy, s32 dx); /* atan2-style heading toward a point */
extern void sub_080113A8(void *sprite, void *animState);
extern s32 sub_0801473C(s32 fromAngle, s32 toAngle); /* -1/0/1 shortest turn */
extern void sub_080146D0(void *work, s32 heading, s32 speed);
extern void sub_0801165C(void *work, s32 accelY);

struct S_02025FF0_174C { u8 pad[0x174C]; u32 lo; u32 hi; };
extern struct S_02025FF0_174C gMainWorkspace;

/* Steers a chasing actor: advances its animation and turn phase, nudges its
 * heading toward the target while the turn timer allows, then applies that
 * heading to its velocity and integrates its motion. */
void sub_08035220(u8 *self) {
    void *sprite = *(void **)(self + 0x38);
    u8 *work = *(u8 **)(self + 0x3C);
    u8 *animState = work + 0x34;
    u8 *steer = work + 0x48;
    s32 turnPhase;
    s32 heading;
    s32 turnDir;

    sub_080113A8(sprite, animState);

    turnPhase = *(s32 *)(work + 0x48) + 0x800;
    *(s32 *)(work + 0x48) = turnPhase;
    if (turnPhase > 0x10000) {
        *(s32 *)(work + 0x48) = 0x10000;
    }
    if (*(u8 *)(steer + 8) <= 0xB3) {
        *(u8 *)(steer + 8) = *(u8 *)(steer + 8) + 1;
        heading = *(s32 *)(steer + 4);
        {
            s32 deltaY = (s32)gMainWorkspace.hi - *(s32 *)(work + 0x0C);
            s32 deltaX = (s32)gMainWorkspace.lo - *(s32 *)(work + 8);
            turnDir = sub_0801473C(heading, sub_08005910(deltaY, deltaX));
        }
        if (turnDir != -1) {
            if (turnDir == 1) {
                *(s32 *)(steer + 4) = *(s32 *)(steer + 4) + 0x180;
            }
        } else {
            *(s32 *)(steer + 4) = *(s32 *)(steer + 4) + 0xFFFFFE80;
        }
        *(s32 *)(steer + 4) = (u16)*(s32 *)(steer + 4);
    }
    sub_080146D0(work, *(s32 *)(steer + 4), *(s32 *)steer);
    sub_0801165C(work, 0);
}
