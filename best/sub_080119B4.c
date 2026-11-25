extern s32 sub_080159BC(s32, s32, s32, s32, s32);
extern s32 sub_08007D7C(s32, s32, s32);
extern s32 sub_08012A94(s32, s32);

struct Obj {
    u16 flags;
    u16 flags2;
    s32 unk4;
    s32 x;
    s32 y;
    u16 unk6;
    s32 unk10;
    s32 unk14;
    u8 pad18[0x28];
};

extern u32 D_02025FF0[];
extern u32 D_02023130[];
extern u32 D_080CB278[];

void sub_080119B4(struct Obj *a, s32 b, u32 c, s32 d, s32 e)
{
    s32 sp00, sp04, sp08, sp0C, sp10, sp1C;
    s32 r6, r8;
    s32 base, t, probe, px, py, res;
    s32 *tab;
    u16 m;
    s32 v, x, m1, m2, x2, r5v;

    sp1C = d;
    r8 = 0;
    a->flags2 = 0;

    if (a->unk10 == 0)
        goto L_DA0;

    r6 = a->unk10;
    a->unk14 = 0;
    r8 = 0;

    if (!(a->unk4 & 0x10))
        goto L_C26;

    if (r6 < 0)
        goto L_9EE;
    goto L_AF2;

L_9EE:
    sp00 = a->unk6 | 0x200;
    sp04 = (s32)&sp08;
    sp08 = 0;
    sub_080159BC(r6, 0, sp08, 0, 0);
    if (sp0C == 1)
    {
        sp0C = 0;
        if ((sp08 & 6) != 0)
            a->flags2 |= 0x100;
    }
    if ((*(u16 *)&sp08 & 6) != 0)
        a->flags2 |= 0x200;
L_A40:
    if (c != 0)
    {
        sub_080159BC(r6, r8, sp08, 0, 0);
        if (sp0C == 1)
        {
            if ((sp08 & 6) != 0)
                a->flags2 |= 0x400;
        }
        if ((sp08 & 8) != 0)
            a->flags2 |= 0x800;
    }
L_A9E:
    sub_080159BC(r6, r8, sp08, 0, 0);
    if (sp0C == 1)
    {
        if ((sp08 & 6) != 0)
            a->flags2 |= 0x100;
    }
L_ADA:
    if (c == 0)
        goto L_C26;
L_AE0:
    sub_080159BC(r6, r8, sp08, 0, 0);
L_AF2:
    sub_080159BC(r6, r8, sp08, 0, 0);
L_BA8:
    sub_080159BC(r6, r8, sp08, 0, 0);
L_BE4:
    if (c == 0)
        goto L_C26;
    sub_080159BC(r6, r8, sp08, 0, 0);

L_C26:
    base = D_02025FF0[0x18A8 / 4];
    t = ((u8)base) << 6;
    tab = D_02023130;
    probe = t + (s32)tab;
    px = a->x + r6 - sp1C;
    py = a->y + 0x80000;
    res = sub_08007D7C(probe, px, py);
    res = (s16)(res >> 15);
    m = tab[res];
    if ((m & 0x0E) != 0)
        goto L_C8E;
    probe = t + (s32)tab;
    px = a->x + r6 + e;
    res = sub_08007D7C(probe, px, py);
    res = (s16)(res >> 15);
    m = tab[res];
    if ((m & 0x0E) != 0)
    {
L_C8E:
        a->flags2 |= 0x04;
    }
L_C96:
    x = a->x;
    m1 = x & 0xFFFF0000;
    x2 = x + r6;
    m2 = x2 & 0xFFFF0000;
    if (m1 != m2)
        goto L_CC0;
    a->x = x2;
    goto L_ED8;
L_CC0:
    v = e;
    if (r6 >= 0)
        v = r6 + e;
    else
        v = r6 - sp1C;
    probe = t + (s32)tab;
    px = v;
    py = a->y;
    res = sub_08007D7C(probe, px, py);
    res = (s16)(res >> 15);
    m = tab[res];
    if ((m & 0x0A) != 0)
    {
        if (r6 > 0)
            v = (r6 & 0xFFF80000) + 0xFFFF8000;
        else
            v = (r6 & 0xFFF80000) + 0x88000;
    }
    else
    {
        probe = t + (s32)tab;
        py = a->y - c;
        res = sub_08007D7C(probe, v, py);
        res = (s16)(res >> 15);
        m = tab[res];
        if ((m & 0x0A) != 0)
        {
            if (r6 > 0)
                v = (r6 & 0xFFF80000) + 0xFFFF8000;
            else
                v = (r6 & 0xFFF80000) + 0x88000;
        }
    }
    a->flags2 |= 0x01;
    if (r6 >= 0)
        a->x = v + sp1C;
    else
        a->x = v - e;
    goto L_ED8;
L_DA0:
    r6 = a->unk14;
    r6 += b;
    a->unk14 = r6;
    if (a->unk4 & 0x10)
    {
        sp00 = a->unk6 | 0x200;
        sp04 = (s32)&sp08;
        sp08 = 0;
        sub_080159BC(r6, 0, sp08, 0, 0);
        if (sp0C == 1)
        {
            sp0C = 0;
            if ((sp08 & 6) != 0)
                a->flags2 |= 0x100;
        }
        if ((sp08 & 6) != 0)
            a->flags2 |= 0x200;
        if ((sp08 & 8) != 0)
            a->flags2 |= 0x800;
    }
    else
    {
        sub_080159BC(r6, 0, sp08, 0, 0);
        if (sp0C == 1)
        {
            if ((sp08 & 6) != 0)
                a->flags2 |= 0x100;
        }
        if ((sp08 & 6) != 0)
            a->flags2 |= 0x200;
        if ((sp08 & 8) != 0)
            a->flags2 |= 0x800;
    }
    {
        s32 dx = a->x - sp1C;
        s32 r5r = sub_08012A94(dx, 2);
        s32 xp = a->x + e;
        s32 r1r = sub_08012A94(xp, 2);
        if (r1r > r5r)
            r1r = r5r;
        if (r1r <= r6)
        {
            a->y = a->y + r6;
        }
        else
        {
            a->y = a->y + r1r;
            a->flags2 |= 0x04;
            a->unk14 = 0;
        }
        if (a->flags2 & 0x100)
            a->unk14 = 0;
    }
L_ED8:
    return;
}
