struct Ent {
    u8 _00[2];
    u16 f02;
    u16 f04;
    s32 x;
    s32 y;
    s32 w;
    s32 h;
};
struct Res { u16 f0; s32 f4; s32 f8; };
extern u8 D_02025FF0[];
extern u8 D_02023130[];
extern u8 D_080D0054[];
extern s32 D_000018A8;
extern s32 sub_08007DD8(s32, s32, s32);
extern void sub_08012704(s32, s32, s32, s32, struct Res *);
extern s32 sub_08015850(s32, s32, s32, s32, s32, s32);
extern void sub_0805DB1C(s32, s32, s32, s32, s32, struct Res *);

void sub_0805D9A4(struct Ent *e, s32 arg1)
{
    struct Res res;
    s32 w;
    s32 h;
    s32 v;
    s32 t;
    u16 fl;

    if (sub_08015850(e->x, e->y, 0xFFFFFF00, 0x100, 0xFFFFFF00, 0x100) == 0)
        return;
    if ((e->f04 & 2) != 0)
        goto l_d9f8;
    h = e->h;
    if (h < 0)
        goto l_d9f8;
    if ((e->f02 & 4) == 0)
        goto l_d9f8;
    t = (u16)(e->f04 & 4);
    if (t == 0)
        goto l_daa6;
l_d9f8:
    w = e->w;
    e->h = h + arg1;
    if (h < 0)
        goto l_da60;
    {
        u8 *p = (u8 *)((u32)D_02025FF0 + (u32)D_000018A8);
        u32 base = (u32)D_02023130;
        v = sub_08007DD8(base + (p[0] << 6), e->x, e->y);
        fl = *(u16 *)(D_080D0054 + ((u32)(u16)v << 1));
        if ((fl & 4) != 0)
            goto l_da60;
        v = sub_08007DD8(base + (p[0] << 6), e->x + w, e->y);
        fl = *(u16 *)(D_080D0054 + ((u32)(u16)v << 1));
        if ((fl & 4) != 0)
            goto l_da60;
        if ((e->f04 & 4) == 0)
            goto l_da8c;
    }
l_da60:
    sub_0805DB1C(e->x, e->y, w, h, 0x0A, &res);
    goto l_daa0;
l_da8c:
    sub_0805DB1C(e->x, e->y, w, h, 0x0E, &res);
l_daa0:
    e->f02 = res.f0;
    return;
l_daa6:
    e->h = t;
    w = e->w;
    sub_08012704(e->x, e->y, w, 0, &res);
    if ((res.f0 & 2) == 0)
        goto l_daf8;
    if ((e->f04 & 8) != 0)
        goto l_daf8;
    sub_0805DB1C(e->x, e->y, e->x + w - res.f4, 0, 0x0A, &res);
    e->x = res.f4;
    e->y = res.f8;
    e->f02 = res.f0;
    return;
l_daf8:
    e->f02 = res.f0 | 4;
    e->x = res.f4;
    e->y = res.f8;
}
