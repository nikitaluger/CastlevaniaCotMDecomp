extern s32 scaleByRandom(s32);
extern s32 randomSignedOffset(s32);
extern void sub_08091B80(s32, s32, s32, s32, s32);
extern void sub_080C31E4(void *, void *, s32);
extern u8 D_08100860[];

/* Select an animation value from a table by index, periodically spawn a child
 * effect at a jittered position, then count the timer down and advance the
 * script step when it underflows. */
void sub_080947A8(u8 *actor) {
    u8 *sprite = *(u8 **)(actor + 0x38);
    u8 *state = *(u8 **)(actor + 0x3C);
    u8 *timerPtr = state + 0x34;
    u8 *animTable = D_08100860;
    s32 animIndex = *(s32 *)(state + 0x34);
    s32 animOffset = animIndex * 10;
    u8 *spawnX;
    s32 spawnY, spawnZ;
    s32 *eventPtr;
    u32 scriptOffset;
    s32 timer, timerBits;

    animTable += 2;
    *(u16 *)(sprite + 0x28) = *(u16 *)(animTable + animOffset);
    timerBits = *(u16 *)(timerPtr + 0x0C);
    if ((timerBits & 7) == 0) {
        spawnX = *(u8 **)(state + 8) + randomSignedOffset(0xE0 << 12);
        spawnY = *(s32 *)(state + 0x0C) + randomSignedOffset(0x80 << 10);
        spawnZ = scaleByRandom(0x80 << 8) + (0x80 << 6);
        sub_08091B80((s32)spawnX, spawnY, 0, spawnZ, 0x16C1);
    }
    timer = *(u16 *)(timerPtr + 0x0C);
    timer = timer - 1;
    *(u16 *)(timerPtr + 0x0C) = timer;
    if ((timer << 16) < 0) {
        *(u16 *)(timerPtr + 0x0C) = 6;
        scriptOffset = *(s16 *)(actor + 0x22);
        scriptOffset <<= 1;
        scriptOffset += (u32)actor;
        *(u8 *)(scriptOffset + 0x19) = 0;
        eventPtr = (s32 *)0x08671BB0;
        sub_080C31E4(actor + 0x18, actor + 0x22, *eventPtr);
    }
}
