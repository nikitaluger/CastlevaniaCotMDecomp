extern s32 sub_08005910(s32, s32);
extern void sub_080269A8(void *, s32);
extern void sub_080C31E4(void *, void *, void *);
extern u8 D_02025FF0[];
extern void *D_08671BB0;

void sub_08026520(u8 *arg0)
{
    u8 *p3C = *(u8 **)(arg0 + 0x3C);
    u8 *p34 = p3C + 0x34;
    u8 *pDC;
    u8 *p48;
    s32 zero;
    u32 base;

    if (*(u8 *)(p34 + 1) != 2 || *(s32 *)(p34 + 4) != 1)
        return;

    pDC = p3C + 0xDC;
    *(s32 *)(pDC + 0) = 0xA0 << 10;
    base = (u32)D_02025FF0;
    {
        s32 a = *(s32 *)(base + 0x1750) - *(s32 *)(p3C + 0xC);
        s32 b = *(s32 *)(base + 0x174C) - *(s32 *)(p3C + 8);
        *(s32 *)(pDC + 4) = sub_08005910(a, b);
    }
    zero = 0;
    *(s32 *)(pDC + 8) = zero;
    *(s32 *)(pDC + 0xC) = 0xA0 << 10;
    *(s32 *)(pDC + 0x10) = zero;
    *(s32 *)(pDC + 0x14) = 0x80 << 1;
    *(s32 *)(pDC + 0x1C) = 0x78;
    *(s32 *)(pDC + 0x20) = 0xC0 << 6;
    *(u16 *)(pDC + 0x1A) |= 0x18;
    *(u16 *)(pDC + 0x18) = zero;
    *(s32 *)(pDC + 0x24) = zero;
    *(s32 *)(pDC + 0x28) = zero;
    p48 = p3C + 0x48;
    *(s32 *)(p48 + 0x68) = *(s32 *)(p3C + 8);
    *(s32 *)(p48 + 0x6C) = *(s32 *)(p3C + 0xC);
    *(s32 *)(p48 + 0x18) = 0xC0 << 8;
    sub_080269A8(arg0, 0x10);
    *(u8 *)(arg0 + *(s16 *)(arg0 + 0x22) * 2 + 0x19) = 0;
    {
        void **lit = &D_08671BB0;
        sub_080C31E4(arg0 + 0x18, arg0 + 0x22, *lit);
    }
}
