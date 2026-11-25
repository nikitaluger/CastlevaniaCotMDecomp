/* Turn the entity one small step toward the global target point and apply the
 * new rotation to its sprite; when the current script step asks for it, spawn a
 * marker object at the entity's position. */
extern s32 sub_08005910(s32, s32);
extern void sub_080113A8(void *, void *);
extern void sub_0801165C(void *, s32);
extern void sub_080146D0(void *, u16, s32);
extern s32 sub_0801473C(void *, s32);
extern void *sub_0805FAEC(void *, s32);

struct GlobalTarget {
    u8 _0[0x174C];
    u32 targetX;
    u32 targetY;
};
extern struct GlobalTarget D_02025FF0;

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
        targetAngle = sub_08005910(D_02025FF0.targetY - *(s32 *)((u8 *)motion + 0x0C),
                                   D_02025FF0.targetX - *(s32 *)((u8 *)motion + 0x08));
        turnDir = sub_0801473C(angleVal, targetAngle);
        turnDir = turnDir << 9;
        newAngle = *(s32 *)((u8 *)entity + 0x6C);
        newAngle = newAngle + turnDir;
        newAngle = newAngle & 0xFFFF;
        *(s32 *)((u8 *)entity + 0x6C) = newAngle;
        sub_080146D0(motion, (u16)newAngle, 0x1C000);
    }

    sub_0801165C(motion, 0);
    sub_080113A8(gfx, aimPoint);

    scriptMask = (u8)(3) & *(u8 *)((u8 *)entity + *(s16 *)((u8 *)entity + 0x22) * 2 + 0x19);
    if (scriptMask == 0) {
        spawned = sub_0805FAEC(entity, 0x108);
        if (spawned != NULL) {
            *(s32 *)((u8 *)spawned + 0x4C) = *(s32 *)((u8 *)motion + 0x08);
            *(s32 *)((u8 *)spawned + 0x5C) = *(s32 *)((u8 *)motion + 0x0C);
            *(u8 *)((u8 *)spawned + 0x7C) = 1;
        }
    }
}
