extern void advanceMotion(void *, s32);
extern void stepAnimationTrack(void *, void *);
extern s32 terrainHasSolidFlags(s32, s32);
extern void setAnimationFrame(void *, void *, s32, s32);
extern void copyPoseAttrs(void *, u32);
extern void sub_080C31E4(void *, void *, u32);

/* Advance a patrolling entity. Integrates its motion (state +8/+C position,
 * +10/+14 velocity, +34 status byte) and animation, then decrements the +0x4C
 * countdown. When the countdown expires or the tile one step ahead -- 0x200000
 * in the direction of vx, via terrainHasSolidFlags -- is blocked, switch to animation
 * 5, copy fresh motion parameters from the 0x080CF9C4 table into the +0x28
 * sub-object, clear the slot timer and dispatch the gScriptStepCallbackTable callback. */
void sub_0804CFC0(void *entity) {
    s32 animHandle;
    void *state;
    u8 *status;
    s32 countdown;
    u32 *callbackTable;
    s32 velX;
    s32 lookAhead;

    animHandle = *(s32 *)((u8 *)entity + 0x38);
    state = *(void **)((u8 *)entity + 0x3C);
    status = (u8 *)state + 0x34;
    advanceMotion(state, 0);
    stepAnimationTrack((void *)animHandle, status);
    countdown = *(u16 *)((u8 *)entity + 0x4C) - 1;
    *(u16 *)((u8 *)entity + 0x4C) = countdown;
    velX = *(s32 *)((u8 *)state + 0x10);
    lookAhead = 0x200000;
    if (velX < 0) lookAhead = 0xFFE00000;
    if ((countdown << 16) == 0 || terrainHasSolidFlags(*(s32 *)((u8 *)state + 8) + lookAhead, *(s32 *)((u8 *)state + 0xC)) != 0) {
        setAnimationFrame((void *)animHandle, status, 5, 0);
        copyPoseAttrs(*(void **)((u8 *)state + 0x28), 0x080CF9C4);
        *(s8 *)((s8 *)((u32)(*(s16 *)((u8 *)entity + 0x22)) * 2 + (u32)entity) + 0x19) = 0;
        callbackTable = (u32 *)0x08671BB0;
        sub_080C31E4((u8 *)entity + 0x18, (u8 *)entity + 0x22, *callbackTable);
    }
}
