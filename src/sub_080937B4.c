extern s32 sub_08005820(s32);
extern s32 sub_0800583C(s32);
extern void sub_0808E348(s32, s32, s32, s32, s32, s32, s32);
extern void sub_080C31E4(void *, void *, s32);
extern s32 sub_080C36E4(s16, s32);
extern u8 D_081007D0[];
extern u32 gMainObjTimerCallback;

/* Selects an animation value from a table by index, periodically spawns a
 * child effect at a jittered position, then counts the timer down and advances
 * the script step when it underflows. */
void sub_080937B4(u8 *arg0) {
    u8 *sprite;
    u8 *state;
    u8 *timerPtr;
    u8 *animTable;
    u8 *animPtr;
    s32 animIndex;
    s32 byteIndex;
    s16 phase;
    s32 spawnX;
    s32 spawnY;
    s32 spawnZ;
    s32 timer;
    u32 *eventPtr;

    sprite = *(u8 **)(arg0 + 0x38);
    state = *(u8 **)(arg0 + 0x3C);
    timerPtr = state + 0x34;
    animTable = D_081007D0;
    animIndex = *(s32 *)(state + 0x34);
    byteIndex = animIndex * 6;
    animPtr = animTable + 2;

    *(u16 *)(sprite + 0x28) = *(u16 *)(animPtr + byteIndex);
    phase = (s16)sub_080C36E4(*(s16 *)(timerPtr + 0x0C), 6);
    if (phase == 0) {
        spawnX = *(s32 *)(state + 8) + sub_0800583C(0xE0000);
        spawnY = *(s32 *)(state + 0x0C) + sub_0800583C(0x20000);
        spawnZ = sub_08005820(0x8000) + 0x2000;
        sub_0808E348(spawnX, spawnY, 0, spawnZ, 0x16C1, phase, 8);
    }
    timer = *(u16 *)(timerPtr + 0x0C) - 1;
    *(u16 *)(timerPtr + 0x0C) = timer;
    if ((timer << 16) <= 0) {
        *(u16 *)(timerPtr + 0x0C) = 0x10;
        *(u8 *)(arg0 + *(s16 *)(arg0 + 0x22) * 2 + 0x19) = 0;
        eventPtr = &gMainObjTimerCallback;
        sub_080C31E4(arg0 + 0x18, arg0 + 0x22, *eventPtr);
    }
}
