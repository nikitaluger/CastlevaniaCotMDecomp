/* Advance the first phase of a scripted effect: tick its timers, ramp the
 * sub-object velocities, publish its angles to the global angle table, then
 * switch to the next update function once the timer expires. */
extern s32 sub_0808D690(s32, void *, s32);
extern s32 sub_0808D6C4(s32, void *);

void sub_0808D454(u8 *effect)
{
    u8 *fx = *((u8 **)(effect + 0x6C));
    s32 speed1, speed2;
    s32 timer;
    s32 frame;
    s32 angle;
    u32 off;
    u8 *angleTable;

    *((s32 *)(fx + 0x34)) = *((s32 *)(fx + 0x34)) + 1;
    *((u8 *)(fx + 0x39)) = *((u8 *)(fx + 0x39)) + 1;
    *((u8 *)(fx + 0x3A)) = *((u8 *)(fx + 0x3A)) + 1;

    speed1 = 0x10000;
    *((s32 *)(fx + 0x24)) = speed1;
    speed2 = 0x20000;
    *((s32 *)(fx + 0x2C)) = speed2;
    *((s32 *)(fx + 0x28)) = speed1;

    timer = *((s32 *)(fx + 0x34));
    if (timer <= 0x28) {
        sub_0808D690(2, fx + 0x14, speed2);
        sub_0808D690(3, fx + 0x1C, *((s32 *)(fx + 0x2C)));
    } else if (timer <= 0x38) {
        sub_0808D690(0, fx + 4, speed1);
        sub_0808D690(1, fx + 0x0C, *((s32 *)(fx + 0x24)));
    }

    angleTable = (u8 *)0x02021E90;
    angle = *((s16 *)(fx + 6));
    off = 0x1460;
    *((s8 *)(angleTable + off)) = angle;
    angle = *((s16 *)(fx + 0x16));
    off = 0x1464;
    *((s8 *)(angleTable + off)) = angle;
    angle = *((s16 *)(fx + 0x0E));
    off = 0x1462;
    *((s8 *)(angleTable + off)) = angle;
    angle = *((s16 *)(fx + 0x1E));
    off = 0x1466;
    *((s8 *)(angleTable + off)) = angle;
    *((s8 *)(angleTable + 0x1468)) = 0x31;

    frame = *((s32 *)(fx + 0x34));
    if (frame <= 0x38) {
        frame &= 1;
        if (frame != 0) {
            sub_0808D690(0, fx + 8, *((s32 *)(fx + 0x28)));
            sub_0808D690(1, fx + 0x10, *((s32 *)(fx + 0x28)));
        }
    }

    sub_0808D6C4(1, fx);

    if (*((s32 *)(fx + 0x34)) > 0xB4) {
        *((s32 *)(fx + 0x34)) = 0;
        *((s32 *)(fx + 0x24)) = 0x40000;
        *((s32 *)(fx + 0x28)) = 0x80000;
        *((u16 *)(effect + 0x22)) = 0;
        *((s32 *)(effect + 0x14)) = 0x0808D549;
    }
}
