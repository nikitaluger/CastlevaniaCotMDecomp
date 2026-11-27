void sub_08011368(void *, void *, s32, s32);
void sub_080C31E0(void *, void *);

void sub_08020E78(void *arg0) {
    u32 mask = 2;
    u32 zero = 0;
    u8 *base = *(u8 **)((u8 *)arg0 + 0x3C);
    u32 **p = (u32 **)(base + 0x58);
    s32 i = 2;
    do {
        u8 *q = (u8 *)*p;
        if (q != NULL) {
            *(u16 *)(q + 0x6C) |= (u16)mask;
            *p = zero;
        }
        p++;
        i--;
    } while (i >= 0);
}

void sub_0802128A(void *arg0) {
    u8 *p = (u8 *)arg0;
    u32 v38 = *(u32 *)(p + 0x38);
    u8 *q = *(u8 **)(p + 0x3C);
    u8 *r4 = q + 0x34;
    *(u32 *)(q + 0x14) = 0;
    *(u32 *)(q + 0x10) = 0;
    sub_08011368((void *)v38, r4, 0x2D, 0);
    if (*r4 & 2) {
        sub_080C31E0(p, *(void **)(p + 0x24));
    }
}
