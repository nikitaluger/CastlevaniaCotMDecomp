void sub_0802697C(void *arg0) {
    u32 *base = *(u32 **)((u8 *)arg0 + 0x3C);
    u32 one = 1;
    u32 zero = 0;
    u32 *p = base + 0x1A;
    s32 i = 4;
    do {
        u32 *q = (u32 *)*p;
        if (q != 0) {
            u16 v = *(u16 *)((u8 *)q + 0x64);
            v = v | one;
            *(u16 *)((u8 *)q + 0x64) = v;
            *p = zero;
        }
        p++;
        i--;
    } while (i >= 0);
}
