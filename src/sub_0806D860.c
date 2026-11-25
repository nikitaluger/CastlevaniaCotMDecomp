extern u8 D_02025368[];

/* Add delta to the workspace value at +0x2D4, clamping it to the signed max at +0x2D6. */
void sub_0806D860(s16 delta)
{
    u8 *base = D_02025368;
    u8 *p = base + 0x2D4;
    s32 newValue = delta + *(u16 *)p;
    *(u16 *)p = newValue;
    if ((s16)newValue > *(s16 *)(base + 0x2D6))
        *(u16 *)p = *(u16 *)(base + 0x2D6);
}
