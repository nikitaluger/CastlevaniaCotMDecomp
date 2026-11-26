extern void sub_08003A6C(void *, s32, void *);
extern void sub_0806D588(void *, void *);
extern void sub_08071A20(void *, s32);
extern void _call_via_r1(void *, u32);
extern void _call_via_r2(void *, void *, void *);
extern u8 gMainWorkspace[];

void sub_0806FDFC(u8 *g)
{
    u8 *p;
    u8 *q;
    u8 *o;
    u8 *base;
    u8 *base2;
    u8 *table;
    u8 *anim;
    u16 *t;
    s16 idx;
    u8 b;

    q = *(u8 **)(g + 0x6C) + 4;
    o = *(u8 **)(g + 0x38);
    p = q;
    base = gMainWorkspace;

    if ((u8)(base[0x173A] - 0x10) > 1 || base[0x14EC] == 2) {
        _call_via_r1(g, *(u32 *)(g + 0x24));
        return;
    }
    sub_08071A20(g, 4);
    t = (u16 *)(g + 0x84);
    *(u32 *)p = *(u32 *)(base + ((t[0] == 2) ? 0x1744 : 0x1728));
    if (*(u16 *)(g + 0x84) == 2) {
        table = gMainWorkspace;
        *(u32 *)(p + 4) = *(u32 *)(table + 0x1748) + 0xFFEC0000;
    } else {
        table = gMainWorkspace;
        *(u32 *)(p + 4) = *(u32 *)(table + 0x172C) + 0xFFEC0000;
    }
    sub_0806D588(o, p);
    sub_08003A6C(q + 0x2C, 0, (void *)0x08472A58);
    base2 = gMainWorkspace;
    {
        s32 value = (base2[0x14ED] != 0xA2) ? 0x2BF : 0x57E;
        *(u32 *)(p + 0x10) = value;
        {
            u8 *state = base2 + 0x14EC;
            value = 0;
            *state = value | 1;
        }
        {
            s32 reset = 0;
            *(u16 *)(o + 4) = 0x400 | reset;
            *(u16 *)(o + 6) = 0x400;
            *(u16 *)(o + 8) = value;
            idx = *(s16 *)(g + 0x22);
            *(u8 *)(g + idx * 2 + 0x19) = reset;
        }
    }
    {
        void **cb = (void **)0x08671BB0;
        anim = g + 0x18;
        _call_via_r2(anim, g + 0x22, *cb);
    }
    idx = *(s16 *)(g + 0x22);
    *(u8 *)(g + idx * 2 + 0x19) += 1;
    idx = *(s16 *)(g + 0x22);
    anim += idx * 2;
    b = *anim;
    _call_via_r1(g, *(u32 *)((*(u32 **)(g + 0x14)) + b));
}
