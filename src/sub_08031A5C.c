extern void sub_080C31E8(void *, void *, s32, s32);

/* Countdown handler: tick the first timer word at work+0x4C; when it expires,
 * tick the second one at work+0x4E, clear the current step byte and advance the
 * command script (passing extra argument 1). */
void sub_08031A5C(void *arg0) {
    u8 *p = (u8 *)arg0;
    u8 *work = *(u8 **)(p + 0x3C);
    u8 *timer = work + 0x48;
    s32 value;
    s32 *script;
    value = *(u16 *)(timer + 4);
    value = value - 1;
    *(u16 *)(timer + 4) = value;
    if ((s32)((u16)value << 16) < 0) {
        value = *(u16 *)(timer + 6);
        value = value - 1;
        *(u16 *)(timer + 6) = value;
        *(u8 *)(p + *(s16 *)(p + 0x22) * 2 + 0x19) = 0;
        script = (s32 *)0x08671BD0;
        sub_080C31E8(p + 0x18, p + 0x22, 1, *script);
    }
}
