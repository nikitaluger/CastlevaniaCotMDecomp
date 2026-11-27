extern s32 scaleByRandom(s32);
extern s32 sub_0800583C(s32);
extern void sub_0808E348(s32, s32, s32, s32, s32, s32, s32);
extern void sub_080C31E4(void *, void *, s32);
extern u8 D_08100818[];

/* Look up a value from D_08100818 into the FX object, spawn a randomly offset
 * effect when the timer's low three bits are clear, and tick a countdown that
 * on expiry resets itself, clears the script step byte and posts a message. */
void sub_08093F70(u8 *self)
{
    u8 *fx = *(u8 **)(self + 0x38);
    u8 *fields = *(u8 **)(self + 0x3C);
    u8 *timer = fields + 0x34;
    u8 *valueTable = D_08100818;
    s32 tableIdx = *(s32 *)(fields + 0x34);
    s32 off = tableIdx * 8;
    s32 flag;
    s32 *msgPtr;

    valueTable += 2;
    *(u16 *)(fx + 0x28) = *(u16 *)(valueTable + off);

    flag = *(u16 *)(timer + 0xC);
    if ((flag & 7) == 0) {
        s32 spawnX = *(s32 *)(fields + 8) + sub_0800583C(0xE0 << 12);
        s32 spawnY = *(s32 *)(fields + 0xC) + sub_0800583C(0x80 << 10);
        s32 spawnZ = scaleByRandom(0x80 << 8) + (0x80 << 6);
        sub_0808E348(spawnX, spawnY, 0, spawnZ, 0x16C1, 0, 8);
    }

    {
        s32 timerVal = *(u16 *)(timer + 0xC);
        timerVal = timerVal - 1;
        *(u16 *)(timer + 0xC) = timerVal;
        if ((timerVal << 16) < 0) {
            u32 stepOffset;
            *(u16 *)(timer + 0xC) = 8;
            stepOffset = *(s16 *)(self + 0x22);
            stepOffset <<= 1;
            stepOffset += (u32)self;
            *(u8 *)(stepOffset + 0x19) = 0;
            msgPtr = (s32 *)0x08671BB0;
            sub_080C31E4(self + 0x18, self + 0x22, *msgPtr);
        }
    }
}
