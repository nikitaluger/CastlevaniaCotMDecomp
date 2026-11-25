s32 sub_080604A0(void) {
    u8 *base = (u8 *)0x02021E90;
    u8 temp;
    u16 *timer;
    u8 *p145C;
    u32 t;

    p145C = base + 0x145C;
    temp = *p145C;
    {
        u32 one = 1;
        if ((temp & one) == 0) {
            *p145C = temp | one;
            return 2;
        }
    }

    timer = (u16 *)(base + 0x145A);
    if (*timer == 0) {
        *timer = 0x3C;
    }
    t = *timer;
    t = t - 1;
    *timer = t;
    if ((u16)t != 0) {
        return 2;
    }

    *(s32 *)(base + 0x1454) += 1;

    temp = *p145C & 0xFE;
    *p145C = temp;
    if (temp & 2) {
        u8 val;
        *p145C = temp & 0xFD;
        val = *(base + 0x1444);
        *(base + 0x143C) = val;
    }

    return 0;
}
