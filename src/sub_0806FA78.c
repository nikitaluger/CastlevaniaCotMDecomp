extern s16 scalePercentSaturate16(u16, s32);
extern void sub_080C31E0(void *, s32);
extern void sub_080C31E4(void *, void *, s32);

struct Inner {
    u8 _0;
    u8 f1;
    u8 f2;
    u8 f3;
    u16 f4;
    u16 f6;
    u16 f8;
    u16 fA;
    u16 fC;
    u16 fE;
    s32 f10;
    u16 _14;
    u16 f16;
    u16 f18;
};
struct Outer {
    u8 _0[0x3C];
    struct Inner *p;
};

/* Initialize an actor's stat block from a table value and a difficulty-
 * dependent percentage, record its sprite, then run the script callback. */
void sub_0806FA78(void *script)
{
    u8 *self = (u8 *)script;
    u8 *actor = *(u8 **)(self + 0x6C) + 4;
    s32 sprite = *(s32 *)(self + 0x38);
    u8 *table = (u8 *)0x02025368;
    u16 value;
    s32 percent;
    s32 zero;
    s32 cond;

    ((struct Outer *)actor)->p->f1 = 0;
    ((struct Outer *)actor)->p->f2 = 2;
    ((struct Outer *)actor)->p->f3 = 8;
    ((struct Outer *)actor)->p->f4 = 0;
    ((struct Outer *)actor)->p->f6 = 8;
    ((struct Outer *)actor)->p->f8 = 8;
    ((struct Outer *)actor)->p->fA = 0;
    ((struct Outer *)actor)->p->fC = 0;

    value = *(u16 *)(table + 0x2DE);
    table += 0x8C;
    zero = 0;
    cond = ((s16 *)table)[zero];
    percent = 0x6E;
    if (cond == 1)
        percent = 0xAD;
    ((struct Outer *)actor)->p->fE = scalePercentSaturate16(value, percent);

    ((struct Outer *)actor)->p->f10 = sprite;
    ((struct Outer *)actor)->p->f16 = 0x0F;
    ((struct Outer *)actor)->p->f18 = 0x13;

    *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
    {
        s32 *lit = (s32 *)0x08671BB0;
        u8 *base18 = self + 0x18;
        sub_080C31E4(base18, self + 0x22, *lit);
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) += 1;
        base18 += *(s16 *)(self + 0x22) * 2;
        sub_080C31E0(self, *(s32 *)(*(s32 *)(self + 0x14) + *base18 * 4));
    }
}
