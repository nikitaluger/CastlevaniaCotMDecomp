void sub_080C31E4(void *, void *, s32);

/* Actor step: advance the sprite's +4 and +6 offset fields until the +6 value
 * passes 0xFF, then clamp both to 0x100, flag completion on the control block,
 * clear the script step byte and advance the script. */
void sub_080A4E84(void *arg0)
{
    u8 *self = (u8 *)arg0;
    u8 *sprite = *(u8 **)(self + 0x38);
    u8 *ctrl = *(u8 **)(self + 0x3C);
    u32 spriteOffset = *(u16 *)(sprite + 6) + 6;
    *(u16 *)(sprite + 6) = spriteOffset;
    *(u16 *)(sprite + 4) = *(u16 *)(sprite + 4) - 0x24;
    if ((s16)spriteOffset > 0xFF)
    {
        u16 limit = 0x100;
        *(u16 *)(sprite + 4) = limit;
        *(u16 *)(sprite + 6) = limit;
        *(u8 *)(*(u8 **)(ctrl + 0x28) + 1) = 1;
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
        {
            s32 *callback = (s32 *)0x08671BB0;
            sub_080C31E4(self + 0x18, self + 0x22, *callback);
        }
    }
}
