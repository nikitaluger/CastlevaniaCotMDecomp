extern s32 scaleByRandom(s32);
extern s32 randomSignedOffset(s32);
extern void sub_08091B80(s32, s32, s32, s32, s32);
extern void sub_080C31E4(void *, void *, s32);
extern u16 D_08100860[];

/* Select an animation value from a table by index, periodically spawn a child
 * effect at a jittered position, then count the timer down and advance the
 * script step when it underflows. */
void sub_08094708(void *actor) {
    u8 *self = (u8 *)actor;
    u8 *sprite = *(u8 **)(self + 0x38);
    u8 *state = *(u8 **)(self + 0x3C);
    u8 *timerPtr = state + 0x34;
    u16 *animTable = D_08100860;
    s32 animIndex = *(s32 *)(state + 0x34);
    *(u16 *)(sprite + 0x28) = animTable[animIndex * 5];
    {
        u16 timerValue = *(u16 *)(timerPtr + 0x0C);
        if ((timerValue & 0xF) == 0) {
            s32 spawnX = *(s32 *)(state + 8) + randomSignedOffset(0xE0000);
            s32 spawnY = *(s32 *)(state + 0x0C) + randomSignedOffset(0x20000);
            s32 spawnZ = scaleByRandom(0x8000) + 0x2000;
            sub_08091B80(spawnX, spawnY, 0, spawnZ, 0x16C1);
        }
    }
    {
        s32 timer = *(u16 *)(timerPtr + 0x0C) - 1;
        *(u16 *)(timerPtr + 0x0C) = (u16)timer;
        if ((timer << 16) < 0) {
            *(u16 *)(timerPtr + 0x0C) = 6;
            *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
            {
                s32 *eventPtr = (s32 *)0x08671BB0;
                sub_080C31E4(self + 0x18, self + 0x22, *eventPtr);
            }
        }
    }
}
