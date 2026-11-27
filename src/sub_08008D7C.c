extern void sub_080035E4(void);
extern void sub_08000E98(s32, const void *, u32, s32, s32);
extern s32 sub_080063D4(void *, void *);
extern s32 sub_080C31E4(void *, void *, s32);
extern u32 D_08671BB0;
extern u8 D_02021E90[];
extern vu16 D_03000830;
extern vu32 D_040000D4[];

void sub_08008D7C(u8 *arg0) {
    u16 sp4;
    u16 *q;
    u16 *p;
    vu32 *dma;
    u8 *base = D_02021E90;
    u32 *ep;

    *(u32 *)(base + 0x125C) = 0;
    D_03000830 = D_03000830 & 0xF0FF;
    q = (u16 *)(base + 0x1260);
    {
        u32 mapBase = 0xD800;
        *q = mapBase;
    }
    q = (u16 *)(0x99 << 5);
    p = (u16 *)(base + (u32)q);
    *p = 0;
    q = (u16 *)((u32)q - 0x40);
    p = (u16 *)(base + (u32)q);
    *p = 0;
    q = (u16 *)((u32)q - 0x40);
    p = (u16 *)(base + (u32)q);
    *p = 0;
    *(u16 *)(base + 0x1262) = 8;
    {
        u32 *scrollX = (u32 *)(base + 0x1278);
        u32 *scrollY = (u32 *)(base + 0x127C);
        *scrollY = 0;
        *scrollX = 0;
    }
    sub_080035E4();
    sp4 = 0;
    dma = D_040000D4;
    dma[0] = (u32)&sp4;
    dma[1] = 0xC0 << 19;
    dma[2] = 0x8100C000;
    (void)dma[2];
    sub_08000E98(1, (const void *)0x08645264, 0xA0 << 19, 0x40, 0x10);
    if (*(u32 *)(arg0 + 0x3C) <= 4) {
        sub_080063D4((void *)0x0864292C, (void *)0x06008000);
        sub_080063D4((void *)0x086452A4, (void *)(0xC0 << 19));
    } else {
        sub_080063D4((void *)0x08644680, (void *)0x06008000);
        sub_080063D4((void *)0x08645604, (void *)(0xC0 << 19));
    }
    if (*(u32 *)(arg0 + 0x3C) <= 4) {
        u8 *tab = (u8 *)0x0866CB50;
        u32 v = *(u32 *)(arg0 + 0x3C);
        sub_080063D4(*(void **)(tab + (v << 3)), (void *)0x06009820);
        v = *(u32 *)(arg0 + 0x3C);
        v <<= 3;
        tab += 4;
        sub_080063D4(*(void **)(tab + v), (void *)0x06009B20);
    }
    {
        s16 idx = *(s16 *)(arg0 + 0x22);
        *(u8 *)(arg0 + idx * 2 + 0x19) = 0;
        ep = &D_08671BB0;
        sub_080C31E4(arg0 + 0x18, arg0 + 0x22, (s32)*ep);
    }
}
