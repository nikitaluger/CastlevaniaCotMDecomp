extern void sub_0800168C(u8 *, s32, s32, s32);
extern void sub_080035E4(void);
extern void sub_080063D4(u32 *, void *);
extern void sub_080C2E68(void *, const void *, u32);
extern void sub_08000E98(s32, const void *, u32, s32, s32);
extern void sub_0805FE8C(u8, u8, u8);
extern void sub_0805FEB4(u8);
extern void sub_08005EE4(u16);
extern void sub_080C31E4(u8 *, u8 *, s32);
extern void sub_080C31E0(u8 *, s32);
extern u32 D_08671BB0;
extern u8 D_02021E90[];
extern vu16 D_03000830;
extern vu32 D_040000D4[];

void sub_08008F90(u8 *arg0)
{
    u8 *base;
    u16 sp4;
    u16 *p;
    u32 off;
    u32 *lo;
    u16 v;
    s16 idx;
    u8 *t;
    u8 b;

    sub_0800168C(arg0, 0, 0xCA << 2, 0);
    base = D_02021E90;
    *(u32 *)(base + 0x125C) = 0;
    D_03000830 &= 0xF0FF;
    do { off = 0x95 << 5;
    p = (u16 *)(base + off); } while (0);
    v = 0xD800;
    *p = v;
    *(u16 *)(base + (0x99 << 5)) = 0;
    do { off += 0x40;
    *(u16 *)(base + off) = 0; } while (0);
    p = (u16 *)(base + 0x12A2);
    v = 0xF00;
    *p = v;
    off -= 0x28;
    lo = (u32 *)(base + off);
    off += 4;
    *(u32 *)(base + off) = 0;
    *lo = 0;
    off = 0x93 << 5;
    sub_080C2E68(base + off, (const void *)0x080CAA3C, 0x40);
    sub_080035E4();
    sp4 = 0;
    {
        vu32 *dma = D_040000D4;
        dma[0] = (u32)&sp4;
        dma[1] = 0x06000000;
        dma[2] = 0x8100C000;
        (void)dma[2];
    }
    sub_080063D4((u32 *)0x0865B280, (void *)0x0600A000);
    sub_080063D4((u32 *)0x0865C6DC, (void *)0x0600C000);
    sub_08000E98(1, (const void *)0x0865B220, 0x05000100, 0x60, 0x10);
    sub_08000E98(1, (const void *)0x080CA9FC, 0x050000E0, 4, 0x10);
    {
        u16 *dst = (u16 *)0x06007800;
        u16 val = 0x7000;
        off = 0;
        do {
            *dst = val;
            val = val + 1;
            dst = dst + 1;
            off++;
        } while (off <= 0x3FF);
    }
    sub_0805FE8C(0, 1, 1);
    sub_0805FEB4(8);
    sub_08005EE4(2);
    idx = *(s16 *)(arg0 + 0x22);
    *(u8 *)(arg0 + idx * 2 + 0x19) = 0;
    {
        u32 *ep = &D_08671BB0;
        t = arg0 + 0x18;
        sub_080C31E4(t, arg0 + 0x22, (s32)*ep);
    }
    idx = *(s16 *)(arg0 + 0x22);
    ((u8 *)(arg0 + idx * 2))[0x19]++;
    idx = *(s16 *)(arg0 + 0x22);
    t = t + idx * 2;
    b = *t;
    sub_080C31E0(arg0, *(u32 *)(*(u32 *)(arg0 + 0x14) + b * 4));
}
