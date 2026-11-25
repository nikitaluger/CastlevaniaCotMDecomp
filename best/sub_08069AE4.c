extern void sub_08010320(u8);
extern void sub_0806C5EC(void *, void *, void *, void *);
extern void sub_0806C6B0(void *, void *, void *, void *);
extern void sub_080C31E4(void *, void *, s32);

void sub_08069AE4(u8 *arg0) {
    u8 *self = arg0;
    u8 *r10 = *(u8 **)(self + 0x6C) + 4;
    u8 *r9 = *(u8 **)(self + 0x38);
    u8 *r8 = r10;
    u32 *ctr;
    u32 c;
    u16 sp[16];
    u16 *r5;
    u16 *r12;
    s32 r7;
    volatile u32 *dma;

    sub_0806C5EC(self, r9, r8, r8);
    ctr = (u32 *)(0x02025FF0 + 0x14A8);
    c = *ctr;
    c = c + 1;
    *ctr = c;
    r5 = sp;
    r12 = (u16 *)0x08521F10;
    r7 = 0x0F;
    do {
        u16 t = *r12;
        u32 a = t & 0x1F;
        u32 b = (t & 0x3E0) >> 5;
        u32 d = (t & 0x7C00) >> 10;
        u32 r2 = a * c >> 4;
        u32 r3 = b * c >> 4;
        u32 r1 = d * c >> 4;
        if (r2 > 0x1F) r2 = 0x1F;
        if (r3 > 0x1F) r3 = 0x1F;
        if (r1 > 0x1F) r1 = 0x1F;
        *r5 = (u16)(r2 + (r3 << 5) + (r1 << 10));
        r5++;
        r12++;
        r7--;
    } while (r7 >= 0);
    dma = (volatile u32 *)0x040000D4;
    dma[0] = (u32)sp;
    dma[1] = 0x05000140;
    dma[2] = 0x80000010;
    (void)dma[2];
    if (*ctr > 0x80) {
        sub_08010320(*(u8 *)0x02025FF8);
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
        sub_080C31E4(self + 0x18, self + 0x22, *(u32 *)0x08671BB0);
    }
    sub_0806C6B0(self, r9, r10, r8);
}
