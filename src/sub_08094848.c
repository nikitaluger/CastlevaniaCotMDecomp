extern s32 scaleByRandom(s32);
extern s32 randomSignedOffset(s32);
extern void sub_08091B80(s32, s32, s32, s32, s32);
extern void sub_080C31E4(void *, void *, u32);
extern s32 sub_080C36E4(s16, s32);

extern u8 D_08100860[];

/* Run a scripted effect step: publish a per-kind value to the FX object, occasionally
 * spawn a projectile at a trig-derived offset, and count down a timer that resets the
 * step and posts a message on expiry. */
void sub_08094848(u8 *effect) {
    u8 *fx = *(u8 **)(effect + 0x38);
    u8 *work = *(u8 **)(effect + 0x3C);
    u8 *state = work + 0x34;
    u8 *table;

    table = D_08100860;
    {
        s32 kind = *(s32 *)(work + 0x34);
        s32 tableOffset = kind * 10;
        table = table + 4;
        *(u16 *)(fx + 0x28) = *(u16 *)(table + tableOffset);
    }

    if ((u16)sub_080C36E4(*(s16 *)(state + 0x0C), 6) == 0) {
        s32 spawnX = *(s32 *)(work + 8) + randomSignedOffset(0xE0000);
        s32 spawnY = *(s32 *)(work + 0x0C) + randomSignedOffset(0x20000);
        s32 spawnSpeed = scaleByRandom(0x8000) + 0x2000;
        sub_08091B80(spawnX, spawnY, 0, spawnSpeed, 0x16C1);
    }
    {
        s32 timeLeft = *(u16 *)(state + 0x0C) - 1;
        *(u16 *)(state + 0x0C) = timeLeft;
        if ((timeLeft << 16) <= 0) {
            *(u16 *)(state + 0x0C) = 6;
            *(u8 *)(effect + *(s16 *)(effect + 0x22) * 2 + 0x19) = 0;
            {
                s32 *lit = (s32 *)0x08671BB0;
                sub_080C31E4(effect + 0x18, effect + 0x22, *lit);
            }
        }
    }
}
