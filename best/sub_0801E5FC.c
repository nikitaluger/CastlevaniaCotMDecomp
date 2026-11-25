void sub_08011368(void *, void *, s32, s32);
void sub_080C31E0(void *, void *);

void sub_0801E5FC(void *arg0) {
    void **p = (void **)((u8 *)*(void **)((u8 *)arg0 + 0x3C) + 0x58);
    s32 i = 5;
    do {
        void *q = *p;
        if (q != NULL) {
            *(u16 *)((u8 *)q + 0x5C) |= 2;
            *p = NULL;
        }
        p++;
    } while (--i >= 0);
}

void sub_0801F90C(void *arg0) {
    u8 *obj = (u8 *)arg0;
    u16 idx;
    u8 v;
    sub_08011368(*(void **)(obj + 0x38), (u8 *)*(void **)(obj + 0x3C) + 0x34, 0, 0);
    *(u32 *)(obj + 0x14) = 0x0866D7C0;
    idx = *(u16 *)(obj + 0x22) + 1;
    *(u16 *)(obj + 0x22) = idx;
    ((u8 *)(obj + (s16)idx * 2))[0x19]++;
    v = *(u8 *)(obj + 0x18 + (s16)idx * 2);
    sub_080C31E0(arg0, *(void **)((u8 *)*(u32 *)(obj + 0x14) + (u32)v * 4));
    *(u16 *)(obj + 0x22) = idx - 1;
}

void sub_08020020(void *arg0) {
    if (!(2 & *(u16 *)((u8 *)arg0 + 0x5C))) {
        u32 *base = *(u32 **)(*(u8 **)((u8 *)arg0 + 0x8C) + 0x3C);
        u32 zero = 0;
        u32 *p = base + 0x58;
        s32 i = 5;
        do {
            if (*p == (u32)arg0) *p = zero;
            p++;
        } while (--i >= 0);
    }
}

void sub_08020498(void *arg0, void *arg1) {
    void *p = *(void **)((u8 *)arg1 + 0x28);
    u16 *src = (u16 *)0x080CE794;
    if ((u16)(*(u16 *)((u8 *)arg0 + 0x28) - 0x29) <= 9) {
        *(u8 *)((u8 *)p + 1) = 0;
    }
    *(u16 *)((u8 *)p + 6) = src[0];
    *(u16 *)((u8 *)p + 8) = src[1];
    *(u16 *)((u8 *)p + 0xA) = src[2];
    *(u16 *)((u8 *)p + 0xC) = src[3];
}
