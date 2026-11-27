extern s32 scaleByRandom(s32);
extern s32 randomSignedOffset(s32);
extern void spawnType207Effect(s32, s32, s32, s32, s32, s32, s32);
extern void sub_080C31E4(void *, void *, s32);
extern s16 sub_080C36E4(s16, s32);
extern u16 D_08100818[];
extern u32 gMainObjTimerCallbacks[];

/* Looks up a value from D_08100818 into the FX object, spawns a randomly offset
 * effect when the table check succeeds, and ticks a countdown that, on expiry,
 * resets itself, clears the script step byte and posts a message.
 */
void sub_08093EBC(u8 *self) {
    u8 *fx = *(u8 **)(self + 0x38);
    u8 *fields = *(u8 **)(self + 0x3C);
    u8 *timer = fields + 0x34;
    u16 *valueTable = D_08100818;
    s32 tableIdx = *(s32 *)(fields + 0x34);
    s32 check;
    s32 spawnX, spawnY, spawnZ;
    u32 *msgPtr;

    *(u16 *)(fx + 0x28) = valueTable[tableIdx * 4];

    check = sub_080C36E4(*(s16 *)(timer + 0x0C), 9);
    if (check == 0) {
        spawnX = *(s32 *)(fields + 0x08) + randomSignedOffset(0xE0 << 12);
        spawnY = *(s32 *)(fields + 0x0C) + randomSignedOffset(0x80 << 10);
        spawnZ = scaleByRandom(0x80 << 8) + (0x80 << 6);
        spawnType207Effect(spawnX, spawnY, 0, spawnZ, 0x16C1, check, 8);
    }
    {
        s32 timerVal = *(u16 *)(timer + 0x0C);
        timerVal = timerVal - 1;
        *(u16 *)(timer + 0x0C) = (u16)timerVal;
        if ((timerVal << 16) < 0) {
            *(u16 *)(timer + 0x0C) = 8;
            {
                u32 stepOffset = *(s16 *)(self + 0x22);
                stepOffset <<= 1;
                stepOffset += (u32)self;
                *(u8 *)(stepOffset + 0x19) = 0;
            }
            msgPtr = (u32 *)gMainObjTimerCallbacks;
            sub_080C31E4(self + 0x18, self + 0x22, *msgPtr);
        }
    }
}
