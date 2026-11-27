extern u8 gMenuState[];

void sub_0800FBB4(void *arg0) {
    u8 *self = (u8 *)arg0;
    u8 *sprite = *(u8 **)(self + 0x38);
    u8 *flags = sprite + 0x2A;
    u8 b;
    s8 v;

    b = 0x40 | *flags;
    *flags = b;

    {
        u8 f8 = gMenuState[0xF8];
        u8 raw = *(u8 *)(self + 0x44);
        s32 sv = (s32)raw << 24;
        sv = sv >> 16;
        sv = sv >> 8;
        if ((s32)f8 == sv) {
            *(u32 *)(sprite + 0x24) = 0x08642884;
        } else {
            *(u32 *)(sprite + 0x24) = 0x08642894;
        }
    }

    v = *(s8 *)(self + 0x44);
    if (v == 0) goto case0;
    if (v == 1) goto case1;
    goto end;

case0:
    *(u32 *)(sprite + 0x14) = (gMenuState[0x41] << 0x14) + (0xC0 << 0xE);
    *(u32 *)(sprite + 0x18) = 0xFFF80000;
    goto end;

case1:
    *(u32 *)(sprite + 0x14) = (gMenuState[0x40] << 0x14) + (0xC0 << 0xE);
    *(u32 *)(sprite + 0x18) = (0x80 << 0xE);

end:
    return;
}
