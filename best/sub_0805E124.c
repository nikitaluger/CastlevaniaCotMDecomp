extern void sub_08007E24(u16);
extern void sub_08005E80(s32);
extern void sub_080C31E4(void *, void *, u32);
extern void sub_080C31E0(void *, void *);

void sub_0805E124(u8 *self)
{
    u32 base = 0x02025368;
    u8 *p = (u8 *)base;
    u8 *r4 = *(u8 **)(self + 0xAC);
    u32 off;

    {
        u16 t = *(u16 *)r4;
        u32 v = 4;
        v |= t;
        *(u16 *)r4 = (u16)v;
    }
    sub_08007E24(*(u16 *)(*(u8 **)(r4 + 4) + 8));

    switch (*(u16 *)(*(u8 **)(r4 + 4) + 6) & 0x0F) {
    case 0: off = 0x3C4; break;
    case 1: off = 0x3C5; break;
    case 2: off = 0x3C6; break;
    default: goto skip;
    }
    p += off;
    *p = (u8)(*p + 1);

skip:
    sub_08005E80(0x1B3);

    {
        u8 *p18;
        s32 *lit;
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
        lit = (s32 *)0x08671BB0;
        p18 = self + 0x18;
        sub_080C31E4(p18, self + 0x22, *lit);
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) += 1;
        p18 = p18 + *(s16 *)(self + 0x22) * 2;
        sub_080C31E0(self, *(void **)((u32)*p18 * 4 + *(u32 *)(self + 0x14)));
    }
}
