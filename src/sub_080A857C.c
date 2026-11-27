extern s32 getAngleFromDelta(s32, s32);
extern s32 sub_0801473C(s32, s32);
extern s32 angleWithinRange(s32, s32, s32);

struct PlayerPosition { u8 _0[0x174C]; s32 playerX; s32 playerY; };
extern struct PlayerPosition gMainWorkspace;

/* Computes a heading toward the player, expressed relative to the work state's
 * facing direction and clamped to within plus or minus 0x1800. */
s32 sub_080A857C(void *arg0, void *arg1) {
    s32 desiredAngle;
    s32 baseAngle;
    s32 deltaX;
    s32 deltaY;
    desiredAngle = getAngleFromDelta(gMainWorkspace.playerY - (*(s32 *)((u8 *)arg1 + 0x94) + *(s32 *)((u8 *)arg0 + 0x6C)),
                      gMainWorkspace.playerX - (*(s32 *)((u8 *)arg1 + 0x90) + *(s32 *)((u8 *)arg0 + 0x5C)));
    deltaX = *(s32 *)((u8 *)arg1 + 0x90) - *(s32 *)((u8 *)arg1 + 0x7C);
    deltaY = *(s32 *)((u8 *)arg1 + 0x94) - *(s32 *)((u8 *)arg1 + 0x80);
    baseAngle = getAngleFromDelta(deltaY, deltaX) & 0xFFFF;
    if (angleWithinRange(baseAngle, 0xC0 << 5, desiredAngle) != 0) {
        return desiredAngle - baseAngle;
    }
    if (sub_0801473C(baseAngle, desiredAngle) == 1) {
        return 0xC0 << 5;
    }
    return 0xFFFFE800;
}
