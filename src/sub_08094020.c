extern s32 scaleByRandom(s32);
extern s32 sub_0800583C(s32);
extern void sub_0808E348(s32, s32, s32, s32, s32, s32, s32);
extern void sub_080C31E4(void *, void *, s32);
extern s32 sub_080C36E4(s16, s32);
extern u8 D_08100818[];
extern u32 gMainObjTimerCallbacks;

/* Entity FX update: copies a value looked up from D_08100818 (indexed by the
 * entity's field 0x34) into the FX object, spawns a positioned effect when a
 * scaled countdown check is zero, then ticks the countdown; on expiry it
 * resets the timer, clears the script-step byte and posts a message.
 */
void sub_08094020(u8 *self) {
    u8 *fx;
    u8 *fields;
    u8 *timer;
    u8 *valueTable;
    u8 *valueEntry;
    s32 tableIdx;
    s32 tableOff;
    s16 check;
    s32 spawnX;
    s32 spawnY;
    s32 spawnZ;
    s32 timerVal;
    u32 *msgPtr;

    fx = *(u8 **)(self + 0x38);
    fields = *(u8 **)(self + 0x3C);
    timer = fields + 0x34;
    valueTable = D_08100818;
    tableIdx = *(s32 *)(fields + 0x34);
    tableOff = tableIdx * 8;
    valueEntry = valueTable + 4;

    *(u16 *)(fx + 0x28) = *(u16 *)(valueEntry + tableOff);
    check = (s16)sub_080C36E4(*(s16 *)(timer + 0x0C), 6);
    if (check == 0) {
        spawnX = *(s32 *)(fields + 8) + sub_0800583C(0xE0000);
        spawnY = *(s32 *)(fields + 0x0C) + sub_0800583C(0x20000);
        spawnZ = scaleByRandom(0x8000) + 0x2000;
        sub_0808E348(spawnX, spawnY, 0, spawnZ, 0x16C1, check, 8);
    }
    timerVal = *(u16 *)(timer + 0x0C) - 1;
    *(u16 *)(timer + 0x0C) = timerVal;
    if ((timerVal << 16) <= 0) {
        *(u16 *)(timer + 0x0C) = 8;
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
        msgPtr = &gMainObjTimerCallbacks;
        sub_080C31E4(self + 0x18, self + 0x22, *msgPtr);
    }
}
