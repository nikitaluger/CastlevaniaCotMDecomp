/* Turn the entity one small step toward the global target point and apply the
 * new rotation to its sprite; when the current script step asks for it, spawn a
 * marker object at the entity's position. */
extern s32 getAngleFromDelta(s32, s32);
extern void stepAnimationTrack(void *, void *);
extern void advanceMotion(void *, s32);
extern void setPolarOffset(void *, u16, s32);
extern s32 getAngleTurnDirection(void *, s32);
extern void *spawnBudgetedEffect(void *, s32);

struct GlobalTarget {
    u8 _0[0x174C];
    u32 targetX;
    u32 targetY;
};
extern struct GlobalTarget gMainWorkspace;

void sub_08040908(void *entity) {
    void *gfx;
    void *motion;
    u8 *aimPoint;
    void *angleVal;
    void *spawned;
    s32 targetAngle;
    s32 turnDir;
    s32 newAngle;
    u32 scriptMask;

    gfx = *(void **)((u8 *)entity + 0x38);
    motion = *(void **)((u8 *)entity + 0x3C);
    aimPoint = (u8 *)motion + 0x34;

    if (*(u8 *)((u8 *)entity + *(s16 *)((u8 *)entity + 0x22) * 2 + 0x19) == 0x30) {
        *(s32 *)((u8 *)entity + 0x8C) = 0;
    }

    if (*(s32 *)((u8 *)entity + 0x8C) != 0) {
        angleVal = *(void **)((u8 *)entity + 0x6C);
        targetAngle = getAngleFromDelta(gMainWorkspace.targetY - *(s32 *)((u8 *)motion + 0x0C),
                                   gMainWorkspace.targetX - *(s32 *)((u8 *)motion + 0x08));
        turnDir = getAngleTurnDirection(angleVal, targetAngle);
        turnDir = turnDir << 9;
        newAngle = *(s32 *)((u8 *)entity + 0x6C);
        newAngle = newAngle + turnDir;
        newAngle = newAngle & 0xFFFF;
        *(s32 *)((u8 *)entity + 0x6C) = newAngle;
        setPolarOffset(motion, (u16)newAngle, 0x1C000);
    }

    advanceMotion(motion, 0);
    stepAnimationTrack(gfx, aimPoint);

    scriptMask = (u8)(3) & *(u8 *)((u8 *)entity + *(s16 *)((u8 *)entity + 0x22) * 2 + 0x19);
    if (scriptMask == 0) {
        spawned = spawnBudgetedEffect(entity, 0x108);
        if (spawned != NULL) {
            *(s32 *)((u8 *)spawned + 0x4C) = *(s32 *)((u8 *)motion + 0x08);
            *(s32 *)((u8 *)spawned + 0x5C) = *(s32 *)((u8 *)motion + 0x0C);
            *(u8 *)((u8 *)spawned + 0x7C) = 1;
        }
    }
}
