extern u8 D_02021E90[];

void sub_08060C74(u8 arg0, u8 arg1, u8 arg2, u8 *src, u8 *dst)
{
    u8 sp[4];
    u8 t, t2, a, b;
    u32 i, j, k;
    u8 shifted;
    u8 idx;
    s32 out = 0, in = 0;

    t = D_02021E90[0x1439];
    a = t << 4;
    sp[0] = a | t;
    t2 = D_02021E90[0x143A];
    sp[1] = a | t2;
    b = t2 << 4;
    sp[2] = b | t;
    sp[3] = b | t2;

    for (i = 0; i < arg1; i++) {
        shifted = (u8)(src[in] << arg2);
        k = in + 1;
        for (j = 0; j < arg0; j++) {
            idx = (shifted & 0xC0) >> 6;
            dst[out] = sp[idx];
            out++;
            shifted = (u8)(shifted << 2);
        }
        out += 4 - arg0;
        in = k;
    }
}
