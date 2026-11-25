extern u8 D_020227EC[];
s32 sub_08006680(s32, s32);

s32 sub_080067B8(s32 arg0, s32 arg1)
{
    u8 *p;
    s32 r4, r5;
    s32 a, b, c, v;
    s32 z;

    r4 = arg1 - arg0 + 1;
    r5 = arg0;
    if (arg0 <= arg1) {
        u8 *base = D_020227EC;
        u32 off = arg0 * 0x48 + 0x40;
        p = base + off;
        z = 0;
        do {
            a = *(s32 *)p;
            b = *(s32 *)(p + 4);
            c = a + b;
            *(s32 *)p = c;
            if (b < 0) {
                if (c > 0) goto tail;
                v = z;
                goto store;
            } else {
                v = 0x00FFFFFF;
                if (c <= v) goto tail;
                v = v + 1;
            }
        store:
            *(s32 *)p = v;
            r4 -= 1;
        tail:
            p += 0x48;
            r5 += 1;
        } while (r5 <= arg1);
    }
    sub_08006680(arg0, arg1);
    if (r4 != 0) return 0;
    return 1;
}
