struct S_02025FF0 { u8 pad[0x174C]; u32 camX; u32 camY; };
extern struct S_02025FF0 gMainWorkspace;
u16 getAngleFromDelta(s32, s32);
void advanceMotion(void *, s32);
void setPolarOffset(void *, s32, s32);
s32 sub_0801473C(s32, u16);
void sub_080C31E4(void *, void *, s32);

/* Homing actor step: advance a thrust accumulator, aim at the camera by
 * comparing the current heading to the target angle, turn toward it, compute
 * velocity and apply it; on script step 0x3C reset and dispatch the handler. */
void sub_0809FB58(void *actor) {
    u8 *self = actor;
    u8 *work = *(u8 **)(self + 0x3C);
    s32 *thrust = (s32 *)(self + 0x8C);
    s32 oldThrust;
    s32 dy;
    s32 dx;
    u16 targetAngle;
    s32 turn;
    u8 *scriptEntry;
    s32 *handlerTable;

    oldThrust = *thrust;
    if (oldThrust <= 0x17FFF) {
        *thrust = oldThrust + 0x2000;
    }
    dy = (s32)gMainWorkspace.camY - *(s32 *)(work + 0x0C);
    dx = (s32)gMainWorkspace.camX - *(s32 *)(work + 0x08);
    targetAngle = getAngleFromDelta(dy, dx);
    turn = sub_0801473C(*(s32 *)(self + 0x7C), targetAngle);
    turn = turn << 8;
    *(s32 *)(self + 0x7C) = *(s32 *)(self + 0x7C) + turn;
    setPolarOffset(work, *(s32 *)(self + 0x7C), *thrust);
    advanceMotion(work, 0);
    scriptEntry = (u8 *)((s32)*(s16 *)(self + 0x22) * 2 + (s32)self);
    if (scriptEntry[0x19] == 0x3C) {
        scriptEntry[0x19] = 0;
        handlerTable = (s32 *)0x08671BB0;
        sub_080C31E4(self + 0x18, self + 0x22, *handlerTable);
    }
}
