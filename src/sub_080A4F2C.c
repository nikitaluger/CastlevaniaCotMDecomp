extern s32 sub_08011368(void *, void *, s16, s32);
extern s32 sub_080C31E4(void *, void *, u32);

extern s16 D_08101CDC[];

/* Cycles the actor's animation frame counter up or down according to its
 * direction flag; at either end of the cycle, clears the action byte and
 * advances the script. */
void sub_080A4F2C(void *arg0) {
    void *gfx;
    u8 *animState;
    u8 *frameCounterPtr;
    u32 *scriptTable;
    s32 direction;
    u32 frameStep;
    gfx = *(void **)((u8 *)arg0 + 0x38);
    animState = (u8 *)(*(void **)((u8 *)arg0 + 0x3C)) + 0x34;
    if (!(*(u8 *)((u8 *)((u32)(*(s16 *)((u8 *)arg0 + 0x22)) * 2 + (u32)arg0) + 0x19) & 7)) {
        direction = *(s16 *)((u8 *)arg0 + 0x84);
        if (direction < 0) {
            frameCounterPtr = (u8 *)arg0 + 0x8C;
            frameStep = *frameCounterPtr + 1;
        } else {
            frameCounterPtr = (u8 *)arg0 + 0x8C;
            frameStep = *frameCounterPtr - 1;
        }
        *frameCounterPtr = frameStep;
        sub_08011368(gfx, animState, D_08101CDC[*(u8 *)((u8 *)arg0 + 0x8C)], 0);
    }
    frameStep = *(u8 *)((u8 *)arg0 + 0x8C);
    if (frameStep == 0 || frameStep == 4) {
        *(u8 *)((u8 *)((u32)(*(s16 *)((u8 *)arg0 + 0x22)) * 2 + (u32)arg0) + 0x19) = 0;
        scriptTable = (u32 *)0x08671BB0;
        sub_080C31E4((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, *scriptTable);
    }
}
