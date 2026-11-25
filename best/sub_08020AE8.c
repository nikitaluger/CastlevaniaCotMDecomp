extern s16 sub_08005820(void);
extern void sub_08011368(void *, void *, s32, s32);
extern void *sub_0805FAEC(s32, s32);
extern void sub_080C31E4(void *, void *, s32);
extern void *D_08671BB0;
extern u8 D_02025FF0[];
extern u8 D_02021E90[];
extern s16 D_080CE804[];

void sub_08020AE8(u8 *arg0) {
    void *a38 = *(void **)(arg0 + 0x38);
    u8 *p = *(u8 **)(arg0 + 0x3C);
    u8 *p34 = p + 0x34;
    u8 *r4 = p + 0x48;
    u8 *base;
    s32 r6;
    s32 bit;
    s32 x;
    void *ret;
    s16 t8;

    sub_08011368(a38, p34, 5, 0);
    if (*(s16 *)(r4 + 0x1C) <= 0 && *(s16 *)(r4 + 8) <= 0) {
        void **g = &D_08671BB0;
        u8 *a18 = arg0 + 0x18;
        u8 *a22 = arg0 + 0x22;
        u16 mask = 1;
        u8 zero = 0;
        void **v = (void **)(p + 0x58);
        s32 i = 2;
        do {
            if (*v != NULL) {
                *(u16 *)((u8 *)*v + 0x6C) |= mask;
                *v = NULL;
            }
            v++;
            i--;
        } while (i >= 0);
        *(u8 *)((u32)(*(s16 *)(arg0 + 0x22)) * 2 + (u32)arg0 + 0x19) = 0;
        sub_080C31E4(a18, a22, *(s32 *)g);
        return;
    }
    base = D_02025FF0;
    x = *(s32 *)(base + 0x189C);
    bit = (s32)(x + ((u32)x >> 31)) >> 1;
    bit &= 1;
    *(s32 *)(r4 + 0) = bit ? (0x80 << 9) : 0;
    t8 = *(u16 *)(r4 + 8) - 1;
    *(u16 *)(r4 + 8) = t8;
    if (t8 < 0) {
        r6 = 3 - *(s16 *)(r4 + 0x1C);
        if (r6 == 0) {
            *(s16 *)(r4 + 0x20) = sub_08005820();
            x = *(s32 *)(base + 0x174C);
            if (x < 0) x += 0xFFFF;
            *(s16 *)(r4 + 0x1E) = x >> 16;
        }
        ret = sub_0805FAEC(*(s32 *)(base + 0x1870), 0x9C);
        r6 <<= 2;
        *(void **)(r4 + 0x10 + r6) = ret;
        if (ret != NULL) {
            s16 y = *(s16 *)(r4 + 0x1E);
            s16 ang = *(s16 *)(r4 + 0x20);
            u32 idx = (u32)r6 + (u32)ang * 12;
            s16 v1 = D_080CE804[idx >> 1];
            s32 v2;
            s32 yv;
            y += v1;
            v2 = D_080CE804[(idx >> 1) + 1];
            v2 = (v2 << 16) + (s32)0xFFFF8000;
            yv = *(s32 *)((u8 *)D_02021E90 + 0x127C + ((*(u8 *)(base + 0x18A8)) + 1) * 64);
            v2 += yv;
            if (v2 < 0) v2 += 0xFFFF;
            *(s16 *)((u8 *)ret + 0x4C) = y;
            *(s16 *)((u8 *)ret + 0x54) = v2 >> 16;
            *(u32 *)((u8 *)ret + 0x8C) = (u32)arg0;
        }
        *(u16 *)(r4 + 8) = 8;
        t8 = *(u16 *)(r4 + 0x1C) - 1;
        *(u16 *)(r4 + 0x1C) = t8;
        if (t8 == 0) *(u16 *)(r4 + 8) = 0x10;
    }
}
