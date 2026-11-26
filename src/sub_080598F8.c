/* Advance the object's tick counter and periodically spawn a projectile with a
 * spread position and small random jitter; fire a script callback when the
 * state's flag is set. */
extern s32 sub_08005820(s32);
extern void setAnimationFrame(s32, s32, s32, s32);
extern void sub_0805A0B0(s32, s32, s32, s32, s16);
extern void sub_080C31E4(void *, void *, s32);
extern s16 sub_080C364C(s16, s32);
extern s16 sub_080C36E4(s16, s32);
extern s32 gMainObjTimerCallback;

void sub_080598F8(void *object) {
    s16 tick;
    s32 randX;
    s32 spawnX;
    s32 randY;
    u8 *stateTail;
    u8 *state;
    u8 *base = object;
    s32 sprite;
    s32 spriteTarget;
    u32 *scriptFn;

    sprite = *(s32 *)(base + 0x38);
    state = *(u8 **)(base + 0x3C);
    spriteTarget = (s32)state + 0x34;
    stateTail = state + 0x48;
    setAnimationFrame(sprite, spriteTarget, 0x12, 1);
    tick = *(s16 *)(stateTail + 6);
    if (((sub_080C36E4(tick, 0xA) << 0x10) == 0) && (*(s16 *)(stateTail + 6) <= 0x1D)) {
        spawnX = *(s32 *)(state + 8) + (((s32)sub_080C36E4(sub_080C364C(tick, 0xA), 5) - 2) * 0x30000);
        randX = sub_08005820(0x4000);
        randY = sub_08005820(2);
        sub_0805A0B0(spawnX, *(s32 *)(state + 0xC) + 0xFFE80000, 0, randX, randY);
    }
    *(u16 *)(stateTail + 6) = *(u16 *)(stateTail + 6) + 1;
    if (4 & *(u16 *)(state + 2)) {
        *(u8 *)(base + (*(s16 *)(base + 0x22) * 2) + 0x19) = 0;
        scriptFn = &gMainObjTimerCallback;
        sub_080C31E4(base + 0x18, base + 0x22, *scriptFn);
    }
}
