extern u32 sub_080133EC(s32, s32);
extern void sub_0801235C(s32, s32 *, s32 *, s32 *);

s32 sub_080121F8(u8 *arg0, u8 *arg1) {
    u32 x, y, k, b, c;
    u32 raw, m;
    s32 v;

    (void)arg1;

    if (sub_080133EC(*(s32 *)(arg0 + 8), *(s32 *)(arg0 + 0xC)) == 1)
        return 0;

    raw = *(u32 *)(arg0 + 8);
    m = 0xFFFF0000;
    x = raw & m;
    k = 0x8000;
    b = x + k;
    raw = *(u32 *)(arg0 + 0xC);
    y = raw & m;
    c = y + k;

    if (sub_080133EC(b, y + 0x18000) == 1)
        v = 0xC000;
    else if (sub_080133EC(b, y + 0xFFFF8000) == 1)
        v = 0x4000;
    else if (sub_080133EC(x + 0xFFFF8000, c) == 1)
        v = 0;
    else if (sub_080133EC(x + 0x18000, c) == 1)
        v = k;
    else
        return 0;

    return v;
}
