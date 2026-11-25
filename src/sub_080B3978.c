extern void sub_080114DC(void *, void *, s16, s32);
extern void sub_08011528(void *, void *);
extern void sub_08011EE8(void *, u32, s32);
extern s32 sub_080C2F24(u32, u32);
extern s32 sub_08014938(s32);
extern s32 sub_08014900(s32);
extern s32 sub_0801459C(u8 *, u32);
extern void sub_080C31E8(void *, void *, s32, u32);
extern void sub_080C31E4(void *, void *, u32);
extern s16 D_08102B62[];
extern u32 D_08102B68[];
extern u32 D_08102B70[];
extern u32 D_08671BB0;
extern u32 D_08671BD0;
extern u32 D_08671BD8;

void sub_080B3978(u8 *arg0) {
    void *a = *(void **)(arg0 + 0x38);
    u8 *p = *(u8 **)(arg0 + 0x3C);
    u8 *p34 = p + 0x34;
    u8 *p48 = p + 0x48;
    s32 s, c;
    u32 w, zero;

    sub_080114DC(a, p34, D_08102B62[*(u8 *)(p48 + 0x20)], 1);
    sub_08011528(a, p34);
    w = D_08102B68[*(u8 *)(p48 + 0x20)];
    if ((*(u16 *)((u8 *)a + 2) & 0x10) == 0) {
        w = (u32)-(s32)w;
    }
    *(u32 *)(p + 0x10) = w;
    sub_08011EE8(p, 0x4000, 0);
    zero = 0;
    c = *(u16 *)(p48 + 0x1C) - 1;
    *(u16 *)(p48 + 0x1C) = c | zero;
    if ((c << 16) == 0) {
        u32 v = *(u32 *)(p48 + 0x18) + 1;
        *(u32 *)(p48 + 0x18) = v;
        if (sub_080C2F24(v, 3) == 0) {
            u32 *fn;
            (arg0 + *(s16 *)(arg0 + 0x22) * 2)[0x17] = zero;
            fn = &D_08671BD8;
            sub_080C31E8(arg0 + 0x18, arg0 + 0x22, 5, *fn);
        } else {
            u32 *fn;
            (arg0 + *(s16 *)(arg0 + 0x22) * 2)[0x17] = zero;
            fn = &D_08671BD8;
            sub_080C31E8(arg0 + 0x18, arg0 + 0x22, 4, *fn);
        }
        return;
    }
    s = sub_08014938(*(u32 *)(p + 8));
    if ((*(u16 *)((u8 *)a + 2) & 0x10) ? (s == 1) : (s == -1)) {
        if (sub_08014900(*(u32 *)(p + 8)) > 0x400000) {
            *(u8 *)(p48 + 0x20) = 1;
            return;
        }
    }
    s = sub_08014938(*(u32 *)(p + 8));
    if (!((*(u16 *)((u8 *)a + 2) & 0x10) ? (s == 1) : (s == -1))) {
        if (sub_08014900(*(u32 *)(p + 8)) > (s32)D_08102B70[*(u8 *)(p48 + 0x20)]) {
            u32 *fn;
            (arg0 + *(s16 *)(arg0 + 0x22) * 2)[0x19] = 0;
            fn = &D_08671BB0;
            sub_080C31E4(arg0 + 0x18, arg0 + 0x22, *fn);
            return;
        }
    }
    s = sub_08014938(*(u32 *)(p + 8));
    if ((*(u16 *)((u8 *)a + 2) & 0x10) ? (s == 1) : (s == -1)) {
        if (sub_0801459C(p, 0x180000) != 0) {
            u32 *fn;
            (arg0 + *(s16 *)(arg0 + 0x22) * 2)[0x19] = 0;
            fn = &D_08671BD0;
            sub_080C31E8(arg0 + 0x18, arg0 + 0x22, 4, *fn);
        }
    }
}
