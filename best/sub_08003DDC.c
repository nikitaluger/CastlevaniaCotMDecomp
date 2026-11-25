struct S_3DDC {
    u16 f00; u16 f02;
    u8 *f04;
    u32 f08;
    u8 *f0C;
    s16 f10; s16 f12;
    u8 *f14;
    u32 f18; u32 f1C;
    s16 f20; s16 f22;
    u8 f24[0x18];
    u16 f3C; u16 f3E;
};

#define HW(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define CLR2() do { for (i = 3; i >= 0; i--) { HW(dest,2)=0; HW(dest,0)=0; dest += st; } } while (0)
#define CLR4() do { for (i = 3; i >= 0; i--) { HW(dest,6)=0; HW(dest,4)=0; HW(dest,2)=0; HW(dest,0)=0; dest += 0x40; } } while (0)

void sub_08003DDC(struct S_3DDC *a)
{
    s32 xend, xc, yc, yend;
    s32 x, y, i, r8, si, t;
    u32 st, m;
    u8 *p14, *p04, *p0C, *dest, *src, *srcptr;
    u32 w;
    s32 pa, pb;
    u8 *tm;
    u32 a18, a1C;
    s32 tileY, tileX;

    a18 = a->f18 + 0x8000;
    a1C = a->f1C + 0x8000;
    xend = (s32)a18 >> 16;
    yend = (s32)a1C >> 16;
    a->f3C = xend;
    a->f3E = yend;
    xend = xend + a->f20 - 1;
    yend = yend + a->f22 - 1;
    xc = ((s32)a18 >> 19) & -4;
    yc = ((s32)a1C >> 19) & -4;
    xend = (xend >> 3) & -4;
    yend = (yend >> 3) & -4;

    if (a->f00 & 0x100) {
        p14 = a->f14;
        p04 = a->f04;
        st = 16 << (a->f02 >> 14);
        m = st - 1;
        p0C = a->f0C;

        if (yc < 0) {
            if (yc <= -4) {
                for (y = yc; y <= -4; y += 4) {
                    for (x = xc; x <= xend; x += 4) {
                        dest = p14 + st * (y & m) + (x & m);
                        CLR2();
                    }
                }
            }
            yc = 0;
        }
        r8 = (a->f12 - 1) << 2;
        tileY = yc >> 2;
        if (r8 < yend) {
            for (y = r8; y <= yend; y += 4) {
                for (x = xc; x <= xend; x += 4) {
                    dest = p14 + st * (y & m) + (x & m);
                    CLR2();
                }
            }
            yend = r8;
        }
        if (xc < 0) {
            if (yc <= yend) {
                for (y = yc; y <= yend; y += 4) {
                    for (x = xc; x <= -4; x += 4) {
                        dest = p14 + st * (y & m) + (x & m);
                        CLR2();
                    }
                }
            }
            xc = 0;
        }
        r8 = (a->f10 - 1) << 2;
        tileX = xc >> 2;
        if (r8 < xend) {
            if (yc <= yend) {
                for (y = yc; y <= yend; y += 4) {
                    for (x = r8; x <= xend; x += 4) {
                        dest = p14 + st * (y & m) + (x & m);
                        CLR2();
                    }
                }
            }
            xend = r8;
        }
        src = p0C + ((a->f10 * tileY) << 1) + (tileX << 1);
        if (yc <= yend) {
            si = 0;
            for (y = yc; y <= yend; y += 4) {
                for (x = xc; x <= xend; x += 4) {
                    dest = p14 + st * (y & m) + (x & m);
                    w = HW(src, si * 2);
                    t = si + 1;
                    srcptr = p04 + (w << 4);
                    for (i = 3; i >= 0; i--) {
                        HW(dest,0)=HW(srcptr,0);
                        HW(dest,2)=HW(srcptr,2);
                        dest += st;
                        srcptr += 4;
                    }
                    si = t;
                }
                src += a->f10 * 2;
            }
        }
    } else {
        tm = a->f14;
        p04 = a->f04;
        if (a->f02 & 0x4000) {
            pa = 5;
            pb = (a->f02 & 0x8000) ? 4 : 6;
        } else {
            pa = 6;
            pb = (a->f02 & 0x8000) ? 5 : 6;
        }
        p0C = a->f0C;
#define BASE(yy, xx) (tm + (((((yy) & 0x20) >> pb) + (((xx) & 0x20) >> pa)) << 11) + (((yy) & 0x1C) << 6) + (((xx) & 0x1C) << 1))
        if (yc < 0) {
            if (yc <= -4) {
                for (y = yc; y <= -4; y += 4) {
                    for (x = xc; x <= xend; x += 4) {
                        dest = BASE(y, x);
                        CLR4();
                    }
                }
            }
            yc = 0;
        }
        r8 = (a->f12 - 1) << 2;
        tileY = yc >> 2;
        if (r8 < yend) {
            for (y = r8; y <= yend; y += 4) {
                for (x = xc; x <= xend; x += 4) {
                    dest = BASE(y, x);
                    CLR4();
                }
            }
            yend = r8;
        }
        if (xc < 0) {
            if (yc <= yend) {
                for (y = yc; y <= yend; y += 4) {
                    for (x = xc; x <= -4; x += 4) {
                        dest = BASE(y, x);
                        CLR4();
                    }
                }
            }
            xc = 0;
        }
        r8 = (a->f10 - 1) << 2;
        tileX = xc >> 2;
        if (r8 < xend) {
            if (yc <= yend) {
                for (y = yc; y <= yend; y += 4) {
                    for (x = r8; x <= xend; x += 4) {
                        dest = BASE(y, x);
                        CLR4();
                    }
                }
            }
            xend = r8;
        }
        src = p0C + ((a->f10 * tileY) << 1) + (tileX << 1);
        if (yc <= yend) {
            si = 0;
            for (y = yc; y <= yend; y += 4) {
                for (x = xc; x <= xend; x += 4) {
                    dest = BASE(y, x);
                    w = HW(src, si * 2);
                    t = si + 1;
                    srcptr = p04 + (w << 5);
                    for (i = 3; i >= 0; i--) {
                        HW(dest,0)=HW(srcptr,0);
                        HW(dest,2)=HW(srcptr,2);
                        HW(dest,4)=HW(srcptr,4);
                        HW(dest,6)=HW(srcptr,6);
                        dest += 0x40;
                        srcptr += 8;
                    }
                    si = t;
                }
                src += a->f10 * 2;
            }
        }
#undef BASE
    }
    a->f00 |= 0x4000;
}
