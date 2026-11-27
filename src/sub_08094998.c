extern u8 D_08100860[];
extern s32 scaleByRandom(s32);
extern s32 sub_0800583C(s32);
extern void sub_08091B80(s32, s32, s32, s32, s32);
extern void sub_080C31E4(void *, void *, u32);

/* Run a scripted effect step: publish a per-kind value to the FX object, spawn a
 * projectile every fourth frame, and count down a timer that resets the step and
 * posts a message on expiry. */
void sub_08094998(u8 *effect)
{
    u8 *fx;
    u8 *work;
    u8 *state;
    s32 spawnX;
    s32 spawnY;
    s32 spawnSpeed;
    s32 timeLeft;
    u16 frame;
    s16 stepIdx;
    s32 resetTime;
    u8 *table;

    fx = *(u8 **)(effect + 0x38);
    work = *(u8 **)(effect + 0x3C);
    state = work + 0x34;

    table = D_08100860;
    {
        s32 kind = *(s32 *)(work + 0x34);
        s32 tableOffset = kind * 10;
        table = table + 8;
        *(u16 *)(fx + 0x28) = *(u16 *)(table + tableOffset);
    }

    frame = *(u16 *)(state + 0x0C);
    resetTime = 3;
    if ((frame & 3) == 0) {
        spawnX = *(s32 *)(work + 0x08) + sub_0800583C(0xE0000);
        spawnY = *(s32 *)(work + 0x0C) + sub_0800583C(0x20000);
        spawnSpeed = scaleByRandom(0x8000) + 0x2000;
        sub_08091B80(spawnX, spawnY, 0, spawnSpeed, 0x3000);
    }

    timeLeft = *(u16 *)(state + 0x0C) - 1;
    *(u16 *)(state + 0x0C) = (u16)timeLeft;
    if ((s32)(timeLeft << 16) > 0) {
    } else {
        *(u16 *)(state + 0x0C) = (u16)resetTime;
        stepIdx = *(s16 *)(effect + 0x22);
        effect[stepIdx * 2 + 0x19] = 0;
        {
            u32 litbase = (u32)0x08671BB0;
            sub_080C31E4(effect + 0x18, effect + 0x22, *(u32 *)litbase);
        }
    }
}
