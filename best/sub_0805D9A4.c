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
extern u8 gMainWorkspace[];
extern u8 gTilemapPages[];
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
s32 __repair_phase_w;
    s32 h;
    s32 v;
s32 __repair_phase_v;
    s32 t;
    u16 fl;
    s32 temp;
    u8 *__base_D_02025FF0;
    u16 temp2;

    __base_D_02025FF0 = gMainWorkspace;

    if (sub_08015850(e->x, e->y, 0xFFFFFF00, 0x100, 0xFFFFFF00, 0x100) == 0)
        return;
    t = (u16)(e->f04 & 2);
    temp = e->h;
    if (t != 0)
        goto l_d9f8;
    h = temp;
    if (h < 0)
        goto l_d9f8;
    temp2 = e->f02;
    if ((temp2 & 4) == 0)
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
        v = sub_08007DD8(((u32)gTilemapPages) + (((u8 *)((u32)__base_D_02025FF0 + (u32)D_000018A8))[0] << 6), e->x, e->y);
        do { fl = *(u16 *)(D_080D0054 + ((u32)(u16)v << 1)); } while (0);
        if ((fl & 4) != 0)
            goto l_da60;
        __repair_phase_v = sub_08007DD8(((u32)gTilemapPages) + (((u8 *)((u32)__base_D_02025FF0 + (u32)D_000018A8))[0] << 6), e->x + w, e->y);
        fl = *(u16 *)(D_080D0054 + ((u32)(u16)__repair_phase_v << 1));
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
    do { __repair_phase_w = e->w; } while (0);
    do { sub_08012704(e->x, e->y, __repair_phase_w, 0, &res); } while (0);
    if ((res.f0 & 2) == 0)
        goto l_daf8;
    if ((e->f04 & 8) != 0)
        goto l_daf8;
    do { sub_0805DB1C(e->x, e->y, e->x + __repair_phase_w - res.f4, 0, 0x0A, &res); } while (0);
    e->x = res.f4;
    e->y = res.f8;
    e->f02 = res.f0;
    return;
l_daf8:
    e->f02 = res.f0 | 4;
    e->x = res.f4;
    e->y = res.f8;
}
