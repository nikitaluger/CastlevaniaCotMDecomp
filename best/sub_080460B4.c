extern void sub_08011EE8(void *, s32, s32);
extern void sub_080113A8(void *, void *);
extern void sub_08047164(void *, void *, void *, void *);
extern void *sub_0805FAEC(s32, s32);
extern void sub_080C31E4(void *, void *, void *);
extern u8 D_02025FF0[];
extern u8 D_080CF86A[];
extern u8 D_080CF8A2[];
extern u32 D_08671BB0[];

void sub_080460B4(u8 *self)
{
    u8 *parent = *(u8 **)(self + 0x38);
    u8 *obj = *(u8 **)(self + 0x3C);
    u8 *sub = obj + 0x34;
    u8 *state = obj + 0x48;
    u8 *tab;
    u8 *p4C;
    u8 *st;
    void *res;
    s32 sv;
    s32 dir;
    s32 ofs;

    sub_08011EE8(obj, 0x16C1, 0);
    sub_080113A8(parent, sub);
    sub_08047164(self, obj, state, parent);

    {
        u8 *tab1 = D_080CF86A;
        s32 ofs1 = *(u8 *)(self + 0x4C);
        ofs1 *= 2;
        tab1 += 6;
        if (*(u16 *)(parent + 0x28) == *(u16 *)(ofs1 + (s32)tab1))
        {
            if (*(u16 *)(parent + 2) & 0x10)
                sv = 0x00020000;
            else
                sv = 0xFFFE0000;
            *(s32 *)(obj + 0x10) = sv;
        }
    }

    st = state;
    if (*(u8 *)(st + 3) == 0)
    {
        tab = D_080CF86A;
        p4C = self + 0x4C;
        ofs = (*(u8 *)p4C) * 2;
        tab += 0x12;
        if (*(u16 *)(parent + 0x28) == *(u16 *)(tab + ofs))
        {
            *(u8 *)(st + 3) = 1;
            *(s32 *)(obj + 0x10) = 0;
            {
                u8 *g = D_02025FF0;
                s32 arg0v = *(s32 *)(g + 0x1870);
                u8 *tbl2 = D_080CF8A2;
                u8 idx2 = *(u8 *)p4C;
                res = sub_0805FAEC(arg0v, *(u16 *)(tbl2 + idx2 * 2));
            }
            if (res != 0)
            {
                u8 src4c;
                if (*(u16 *)(parent + 2) & 0x10)
                    dir = 1;
                else
                    dir = -1;
                *(u8 *)(res + 0x7C) = (u8)dir;
                *(s32 *)(res + 0x5C) = *(s32 *)(obj + 8) + ((*(s8 *)(res + 0x7C)) << 21);
                *(s32 *)(res + 0x6C) = *(s32 *)(obj + 0x0C);
                src4c = *(u8 *)p4C;
                *(u8 *)(res + 0x4C) = src4c;
            }
        }
    }

    if (*(u8 *)sub & 2)
    {
        u32 *pp;
        *(u8 *)(self + (*(s16 *)(self + 0x22)) * 2 + 0x19) = 0;
        pp = D_08671BB0;
        sub_080C31E4(self + 0x18, self + 0x22, (void *)*pp);
    }
}
