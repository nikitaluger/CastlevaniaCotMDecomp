extern u8 D_02021E90[];
extern u8 D_02025FF0[];
extern u8 D_080E596C[];
extern u8 D_080E598C[];

extern s32 sub_0806D450(void *, void *, void *);
extern void sub_080722E0(void *, u8);
extern void *sub_0808DBF8(s32, s32, u16);
extern s32 sub_08003740(void *, s32);
extern s16 sub_080C364C(s32, s16);
extern void _call_via_r1(void *, void *);

void sub_08080C34(void *arg0) {
    u8 *e = (u8 *)arg0;
    u8 *q = *(u8 **)(e + 0x6C) + 4;
    u8 *spr = *(u8 **)(e + 0x38);
    u8 *entry;
    u8 *t;
    s32 r1v;
    u8 nr2;
    s16 tmp;
    u32 h;
    s16 sh;
    u8 v;
    u32 g58, nr;
    s32 g54, add, v54, r0, m, r4v, r3v;
    u16 flags;
    u8 b;
    u32 idx;
    u32 val0, val1, p10;
    s32 arg0v, arg1v;
    u8 idx2, v2;

    if (sub_0806D450(e, spr, q) > 0) {
        r1v = *(s32 *)(e + 0x24);
        goto L_D4C;
    }

    idx2 = D_080E596C[*(u32 *)(e + 0x9C)];
    entry = D_080E598C + idx2 * 28;

    h = *(u16 *)(spr + 0x04);
    sh = *(s16 *)(spr + 0x04);
    if (sh > 0x100) {
        *(u16 *)(spr + 0x04) = h - 0x40;
        *(u16 *)(spr + 0x06) = *(u16 *)(spr + 0x06) - 0x40;
        t = *(u8 **)(q + 0x2C);
        tmp = sub_080C364C((s32)(*(s16 *)entry) << 8, *(s16 *)(spr + 0x04));
        *(s16 *)(t + 0x06) = tmp;
        t = *(u8 **)(q + 0x2C);
        tmp = sub_080C364C((s32)(*(s16 *)(entry + 2)) << 8, *(s16 *)(spr + 0x06));
        *(s16 *)(t + 0x08) = tmp;
    }

    v = entry[0x11];
    g58 = *(u32 *)(q + 0x58);
    nr = g58 + v;
    nr &= 0xFF;
    nr2 = (u8)nr;
    *(u32 *)(q + 0x58) = nr;
    g54 = *(s32 *)(q + 0x54);
    add = *(s32 *)(entry + 0x14);
    g54 += add;
    *(u32 *)(q + 0x54) = g54;
    if (g54 <= 0x00800000) goto L_CONT;
    r1v = *(s32 *)(e + 0x24);
    goto L_D4C;

L_CONT:
    sub_080722E0(q, nr2);

    v54 = *(s32 *)(q + 0x54);
    r0 = v54 >> 12;
    m = *(s32 *)(q + 0x08);
    r0 = r0 * m;
    if (r0 < 0) r0 += 0x0F;
    r0 >>= 4;
    r4v = r0 + (0xF0 << 15);
    *(s32 *)(spr + 0x14) = r4v;
    v54 = *(s32 *)(q + 0x54);
    r0 = v54 >> 12;
    m = *(s32 *)(q + 0x0C);
    r0 = r0 * m;
    if (r0 < 0) r0 += 0x0F;
    r0 >>= 4;
    r3v = r0 + (0xA0 << 15);
    *(s32 *)(spr + 0x18) = r3v;

    t = *(u8 **)(q + 0x2C);
    flags = *(u16 *)(t + 0x14);
    if ((flags & 1) == 0) goto L_D68;
    if ((flags & 2) != 0) goto L_D68;

    {
        u8 *pt = D_02021E90;
        u8 *pb = D_02025FF0;
        pb += 0x18A8;

        idx = ((u32)*pb + 1) * 0x40;
        val0 = *(u32 *)(pt + 0x1278 + idx);
        arg0v = r4v + val0;

        idx = ((u32)*pb + 1) * 0x40;
        val1 = *(u32 *)(pt + 0x127C + idx);
        arg1v = r3v + val1;
        sub_0808DBF8(arg0v, arg1v, 0);
        q = e;
        r1v = *(s32 *)(q + 0x24);
        goto L_D4C;
    }

L_D68:
    {
        u8 *base2 = D_02025FF0;
        u16 h2 = *(u16 *)(base2 + 0x18C2);
        *(u16 *)(spr + 0x00) = h2;
        sub_08003740(q + 0x1C, (s32)spr);
        v = base2[0x173A];
        if (v != 0x1C) {
            v2 = base2[0x14ED];
            if (v2 != 0) goto L_D9E;
            p10 = *(u32 *)(base2 + 0x10);
            if (p10 == 0) goto L_D9E;
        }
    }
    {
        s32 r1x = *(s32 *)(e + 0x24);
        _call_via_r1(e, (void *)r1x);
    }
    goto L_D9E;

L_D4C:
    _call_via_r1(e, (void *)r1v);

L_D9E:
    (void)0;
}
