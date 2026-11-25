void sub_08015974(void);

void sub_08018410(void *arg0) {
    s32 zero = 0;
    s32 one = 1;
    u8 *base;
    void **p;
    void *q;
    s32 i;
    base = *(u8 **)((u8 *)arg0 + 0x3C);
    p = (void **)(base + 0x80);
    i = 9;
    do {
        q = *p;
        if (q != 0) {
            *(u16 *)((u8 *)q + 0x64) |= one;
            *p = (void *)zero;
        }
        p++;
        i--;
    } while (i >= 0);
}

void sub_0801572C(void *arg0, s32 *arg1, s32 *arg2) {
    s32 t;
    s32 zero;
    t = *(u16 *)((u8 *)arg0 + 0x1E) - 1;
    zero = 0;
    *(u16 *)((u8 *)arg0 + 0x1E) = t;
    if ((t << 16) <= 0) {
        if (*arg1 != 0) { sub_08015974(); *arg1 = zero; }
        if (*arg2 != 0) { sub_08015974(); *arg2 = zero; }
        *(u16 *)arg0 &= 0xFFF7;
    }
}

void sub_0801565C(void *arg0, s32 *arg1, s32 *arg2) {
    s32 t;
    s32 zero;
    t = *(u16 *)((u8 *)arg0 + 0x1E) - 1;
    zero = 0;
    *(u16 *)((u8 *)arg0 + 0x1E) = t;
    if ((t << 16) <= 0) {
        if (*arg1 != 0) { sub_08015974(); *arg1 = zero; }
        if (*arg2 != 0) { sub_08015974(); *arg2 = zero; }
        *(u16 *)arg0 &= 0xFFFB;
    }
}
