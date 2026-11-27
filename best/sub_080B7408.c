extern void *spawnBudgetedEffect(void *, s32);

void sub_080B7408(void *arg0, s32 arg1) {
    void *r4;
    s32 r6;
    void *r5;
    void *r2;
    u16 fl;
    u32 m;
    s32 r3;
    s32 r1;
    r4 = arg0;
    r6 = arg1;
    r5 = *(void **)((u8 *)r4 + 0x3C);
    r2 = spawnBudgetedEffect(r4, 0x1C9);
    if (r2 != 0) {
        *(u32 *)((u8 *)r2 + 0x4C) = *(u32 *)((u8 *)r5 + 8);
        *(u32 *)((u8 *)r2 + 0x5C) = *(u32 *)((u8 *)r5 + 0xC) + 0xFFEC0000;
        fl = *(u16 *)((u8 *)*(void **)((u8 *)r4 + 0x38) + 2);
        m = 0x10;
        m = m & fl;
        r3 = 1;
        r3 = -r3;
        r1 = r3;
        if (m != 0) {
            r1 = 1;
        }
        *(s8 *)((u8 *)r2 + 0x6C) = (s8)r1;
        *(s8 *)((u8 *)r2 + 0x70) = (s8)r6;
    }
}
