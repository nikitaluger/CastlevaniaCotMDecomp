void sub_0805D92C(s32, s32, s32);
s32 sub_0800583C(s32);
s32 sub_08005820(s32);
void sub_0808DBF8(s32, s32, s32);
s32 sub_080C36E4(void *, s32);
void sub_080918B0(s32, s32, s32, s32, s32, s32);
void sub_080C31E4(void *, void *, void *);

extern u8 D_02025368[];
extern u8 D_02025FF0[];
extern u16 D_081005C4[];
extern void *D_08671BB0;

static inline void zeroHalf(u16 *p)
{
    u32 zero = 0;
    *p = (u16)zero;
}

void sub_08091414(u8 *arg0)
{
    u8 *base = D_02025368;
    u8 *r7ptr = *(u8 **)(arg0 + 0xAC);
    u8 *r5 = *(u8 **)(arg0 + 0x3C);
    u16 sp8;
    u16 r2;
    u32 r4;
    s32 x, y;

    r2 = *(u16 *)(*(u8 **)(r7ptr + 4) + 6);
    r4 = r2;
    if (r4 <= 4) {
        u8 b = *(u8 *)(base + 0x2D8);
        if (b != 0) {
            if (r4 == D_081005C4[b - 1]) {
                if (*(s16 *)(base + 0x8C) != 1) {
                    r2 = 6;
                } else if (*(u16 *)(base + 0x2D8) != 1) {
                    r2 = 6;
                }
            }
        }
    }

    sub_0805D92C(*(s32 *)(r5 + 4), *(s32 *)(r5 + 8) + 0xFFF00000, r2);

    {
        u16 v = *(u16 *)r7ptr;
        u16 bit = 4;
        zeroHalf(&sp8);
        *(u16 *)r7ptr = v | bit;
    }

    x = *(s32 *)(r5 + 4) + sub_0800583C(0x40000);
    y = *(s32 *)(r5 + 8) + sub_0800583C(0x20000);
    sub_0808DBF8(x, y, 8);

    x = *(s32 *)(r5 + 4) + sub_0800583C(0xC0000);
    y = *(s32 *)(r5 + 8) + sub_0800583C(0xC0000) + 0xFFF00000;

    r4 = sub_080C36E4(*(void **)&D_02025FF0[0x1898], 5);
    r4 = r4 - 2;
    r4 = r4 << 14;
    sub_080918B0(x, y, r4, 0x8000 - sub_08005820(0x20000), 0x16C1, 0);

    *(u8 *)(arg0 + ((s16 *)arg0)[0x11] * 2 + 0x19) = *(u8 *)&sp8;
    sub_080C31E4(arg0 + 0x18, arg0 + 0x22, D_08671BB0);
}
