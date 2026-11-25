typedef s32 (*Fn)(s32);
extern Fn D_08671BFC[];

void sub_08005258(void) {
    s32 v0, v1, v2, v3, v4, p0, p1, p2, x0, x1;
    s32 a0, a1, a2, b0, b1, b2, b3, b4, nb0, bp0, bx, bp1, by, bp2;
    s32 c0, c1, c2, c3, c4, nc0, cp0, cx, cp1, cy, cp2;
    s32 d0, d1, d2, e0, e1, e2, e3, e4, ep0, ex, ep1, ey, ep2;
    s32 f0, f1, f2, g0, h0, h1, h2;
    Fn *pf = &D_08671BFC[0];

    v0 = (*pf)(*(u16 *)0x0300269C + 0x4000);
    v1 = (*pf)(*(u16 *)0x030026A8 + 0x4000);
    v2 = (*pf)(*(u16 *)0x03002914);
    v3 = (*pf)(*(u16 *)0x0300269C);
    v4 = (*pf)(*(u16 *)0x030026A8);
    if (v0 < 0) v0 += 0xFF;
    p0 = (v0 >> 8) * v1;
    if (p0 < 0) p0 += 0xFFFF;
    x0 = v2; if (x0 < 0) x0 += 0xFF;
    p1 = v3 * (x0 >> 8);
    if (p1 < 0) p1 += 0xFF;
    x1 = v4; if (x1 < 0) x1 += 0xFF;
    p2 = (x1 >> 8) * (p1 >> 8);
    if (p2 < 0) p2 += 0xFFFF;
    *(s32 *)0x02025B90 = (p0 >> 0x10) - (p2 >> 0x10);

    a0 = (*pf)(*(u16 *)0x03002914 + 0x4000);
    a1 = (*pf)(*(u16 *)0x030026A8);
    if (a0 < 0) a0 += 0xFF;
    a2 = (a0 >> 8) * a1;
    if (a2 < 0) a2 += 0xFFFF;
    *(s32 *)0x02025FD8 = a2 >> 0x10;

    b0 = (*pf)(*(u16 *)0x0300269C);
    b1 = (*pf)(*(u16 *)0x030026A8 + 0x4000);
    b2 = (*pf)(*(u16 *)0x03002914);
    b3 = (*pf)(*(u16 *)0x0300269C + 0x4000);
    b4 = (*pf)(*(u16 *)0x030026A8);
    nb0 = -b0; if (nb0 < 0) nb0 += 0xFF;
    bp0 = (nb0 >> 8) * b1; if (bp0 < 0) bp0 += 0xFFFF;
    bx = b2; if (bx < 0) bx += 0xFF;
    bp1 = b3 * (bx >> 8); if (bp1 < 0) bp1 += 0xFF;
    by = b4; if (by < 0) by += 0xFF;
    bp2 = (by >> 8) * (bp1 >> 8); if (bp2 < 0) bp2 += 0xFFFF;
    *(s32 *)0x02025FE0 = (bp0 >> 0x10) - (bp2 >> 0x10);

    c0 = (*pf)(*(u16 *)0x0300269C + 0x4000);
    c1 = (*pf)(*(u16 *)0x030026A8);
    c2 = (*pf)(*(u16 *)0x03002914);
    c3 = (*pf)(*(u16 *)0x0300269C);
    c4 = (*pf)(*(u16 *)0x030026A8 + 0x4000);
    nc0 = -c0; if (nc0 < 0) nc0 += 0xFF;
    cp0 = (nc0 >> 8) * c1; if (cp0 < 0) cp0 += 0xFFFF;
    cx = c2; if (cx < 0) cx += 0xFF;
    cp1 = c3 * (cx >> 8); if (cp1 < 0) cp1 += 0xFF;
    cy = c4; if (cy < 0) cy += 0xFF;
    cp2 = (cy >> 8) * (cp1 >> 8); if (cp2 < 0) cp2 += 0xFFFF;
    *(s32 *)0x02025B94 = (cp0 >> 0x10) - (cp2 >> 0x10);

    d0 = (*pf)(*(u16 *)0x03002914 + 0x4000);
    d1 = (*pf)(*(u16 *)0x030026A8 + 0x4000);
    if (d0 < 0) d0 += 0xFF;
    d2 = (d0 >> 8) * d1; if (d2 < 0) d2 += 0xFFFF;
    *(s32 *)0x02025B98 = d2 >> 0x10;

    e0 = (*pf)(*(u16 *)0x0300269C);
    e1 = (*pf)(*(u16 *)0x030026A8);
    e2 = (*pf)(*(u16 *)0x03002914);
    e3 = (*pf)(*(u16 *)0x0300269C + 0x4000);
    e4 = (*pf)(*(u16 *)0x030026A8 + 0x4000);
    if (e0 < 0) e0 += 0xFF;
    ep0 = (e0 >> 8) * e1; if (ep0 < 0) ep0 += 0xFFFF;
    ex = e2; if (ex < 0) ex += 0xFF;
    ep1 = (ex >> 8) * e3; if (ep1 < 0) ep1 += 0xFF;
    ey = e4; if (ey < 0) ey += 0xFF;
    ep2 = (ey >> 8) * (ep1 >> 8); if (ep2 < 0) ep2 += 0xFFFF;
    *(s32 *)0x02025FD0 = (ep0 >> 0x10) - (ep2 >> 0x10);

    f0 = (*pf)(*(u16 *)0x03002914 + 0x4000);
    f1 = (*pf)(*(u16 *)0x0300269C);
    if (f0 < 0) f0 += 0xFF;
    f2 = (f0 >> 8) * f1; if (f2 < 0) f2 += 0xFFFF;
    *(s32 *)0x02025FE8 = f2 >> 0x10;

    g0 = (*pf)(*(u16 *)0x03002914);
    if (g0 < 0) g0 += 0xFF;
    *(s32 *)0x02025BC0 = g0 >> 8;

    h0 = (*pf)(*(u16 *)0x03002914 + 0x4000);
    h1 = (*pf)(*(u16 *)0x0300269C + 0x4000);
    if (h0 < 0) h0 += 0xFF;
    h2 = (h0 >> 8) * h1; if (h2 < 0) h2 += 0xFFFF;
    *(s32 *)0x02025FD4 = h2 >> 0x10;
}
