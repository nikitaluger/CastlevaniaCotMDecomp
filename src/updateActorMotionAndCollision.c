extern s32 checkGlobalStateChange(void *, void *, void *);
extern s32 getTileTerrainB(u32, s32, s32);
extern void startEffectTimer(void *, s32, u32);
extern void stepDelayTimer(void *, void *);
extern void cullOffscreenEntity(void *, void *);
extern void sub_0806D588(void *, void *);
extern void sub_080C31E0(void *, s32);
extern void sub_080C31E4(void *, void *, s32);
struct S_02025FF0 {
    u8 _0[0x10];
    s32 f10;
    u8 _14[0x14ED-0x14];
    u8 f14ED;
    u8 _14EE[0x173A-0x14EE];
    u8 f173A;
    u8 _173B[0x18A8-0x173B];
    u8 f18A8;
    u8 _18A9[0x19];
    u16 f18C2;
};
extern struct S_02025FF0 gMainWorkspace;
extern s32 gMainObjTimerCallbacks;

/* Advances an entity's motion/animation and checks its collision row; clears
 * its state on a hit, then either dispatches the current handler or applies
 * the remaining per-frame effect. */
/* Advances an entity's motion/animation phase, checks its tile-collision row, clears state on a hit, then either dispatches the current handler or applies the remaining per-frame effect. */ void updateActorMotionAndCollision(u8 *entity) {
    u8 *vector;
    u8 *motion;
    u8 *sprite;
    u8 *state;
    s32 guardResult;
    s32 phaseValue;
    s32 speed;
    s32 phaseStep;
    u32 tableAddr;
    u32 tableBase;
    s32 posX;
    s32 posY;
    s32 collisionResult;
    u8 *stateBytePtr;
    s32 *callbacks;
    u32 stateOffset;

    motion = *(u8 **)(entity + 0x6C);
    vector = motion + 4;
    sprite = *(u8 **)(entity + 0x38);
    state = vector;
    guardResult = checkGlobalStateChange(entity, sprite, state);
    if (guardResult == 0) {
        phaseValue = *(s32 *)(state + 0x0C) + 0x4000;
        *(s32 *)(state + 0x0C) = phaseValue;
        if (phaseValue > 0x80000) *(s32 *)(state + 0x0C) = 0x80000;
        *(s32 *)(motion + 4) = *(s32 *)(motion + 4) + *(s32 *)(state + 8);
        speed = *(s32 *)(state + 4);
        phaseStep = *(s32 *)(state + 0x0C);
        speed = speed + phaseStep;
        *(s32 *)(state + 4) = speed;
        tableBase = 0x02023130;
        tableAddr = ((u32)gMainWorkspace.f18A8 << 6) + tableBase;
        posX = *(s32 *)(motion + 4) + *(s32 *)(state + 8);
        posY = speed + phaseStep;
        collisionResult = getTileTerrainB(tableAddr, posX, posY);
        if (((collisionResult << 16) != 0) || ((*(u16 *)(*(u8 **)(state + 0x2C) + 0x14) & 1) != 0)) {
            startEffectTimer(motion + 0x20, 0, 0x084D2734);
            *(u16 *)(*(u8 **)(state + 0x2C) + 0x14) = (u16)guardResult;
            stateOffset = (u32)(*(s16 *)(entity + 0x22) * 2);
            stateOffset += (u32)entity;
            stateBytePtr = (u8 *)stateOffset;
            *(u8 *)(stateBytePtr + 0x19) = 0;
            callbacks = &gMainObjTimerCallbacks;
            sub_080C31E4(entity + 0x18, entity + 0x22, *callbacks);
        }
        *(u16 *)sprite = gMainWorkspace.f18C2;
        stepDelayTimer(vector + 0x1C, sprite);
        sub_0806D588(sprite, state);
        if ((gMainWorkspace.f173A == 0x1C) ||
            ((gMainWorkspace.f14ED == 0) && (gMainWorkspace.f10 != 0))) {
            sub_080C31E0(entity, *(s32 *)(entity + 0x24));
            return;
        }
        cullOffscreenEntity(entity, sprite);
    }
}
