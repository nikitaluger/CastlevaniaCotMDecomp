struct In {
    u8 _0[0x146C];
    u16 c146C;
    u8 _1[2];
    u16 c1470;
};
struct St {
    u8 _0[0x48];
    u32 *p48;
    u8 _1[0x69 - 0x4C];
    u8 c69;
    s8 c6A;
    u8 c6B[1];
    u8 _2[0x6F - 0x6C];
    u8 c6F[1];
    u8 _3[0x73 - 0x70];
    u8 c73[1];
    u8 _4[0xF3 - 0x74];
    u8 cF3[1];
};
extern struct In D_02021E90;
extern struct St D_020278D0;
extern u32 D_02025368[];
extern void *D_08671BB0;
extern void *D_08671BC0;

void sub_08005E80(s32);
void sub_0800EDAC(s32);
void sub_0800EF3C(s32);
void sub_0800F124(u32);
void sub_0800F1D8(u32, u32);
void sub_0800F3C8(u32, u32);
void sub_0806D930(struct St *);
void sub_080C2E68(struct St *, u8 *, u32);
void sub_080C31E0(void *, void *);
void sub_080C31E4(void *, void *, void *);

void sub_0800D860(u8 *a)
{
    u32 *tbl = D_02025368;
    struct St *g = &D_020278D0;
    s8 *p6A = &g->c6A;
    s32 idx = *p6A;
    u32 r;
    u16 v;
    s32 i;
    u32 t;

    r = 0x300 & D_02021E90.c1470;
    if (r == 0x300) goto D9A4;
    if (r != 0) {
        sub_080C2E68(g, (u8 *)&tbl[0xB1], 0x48);
        sub_0806D930(g);
    }
    r = 0x200;
    r &= D_02021E90.c1470;
    if (r != 0) {
        *p6A = *p6A - 1;
        if ((s8)*p6A < 0) *p6A = 3;
        i = *p6A;
        if (g->cF3[i] == 0) *p6A = *p6A - 1;
        if ((s8)*p6A < 0) *p6A = 3;
    }
    r = 0x100;
    r &= D_02021E90.c1470;
    if (r != 0) {
        *p6A = *p6A + 1;
        if ((s8)*p6A > 3) *p6A = 0;
        i = *p6A;
        if (g->cF3[i] == 0) *p6A = *p6A + 1;
        if ((s8)*p6A > 3) *p6A = 0;
    }
    r = 0x300;
    r &= D_02021E90.c1470;
    if (r != 0) {
        sub_08005E80(0xA7 * 2);
        g->c69 = (g->c69 + 1) & 1;
        sub_0800F124((u8)*p6A);
        sub_0800F1D8((u8)*p6A, g->c69);
        sub_0800F3C8(g->c69, 0);
        sub_0800EDAC(0);
        i = *p6A;
        t = (s8)g->c6B[i];
        t = t + (i << 5);
        sub_0800EF3C(*(u8 *)((u8 *)g + 0x73 + t));
        return;
    }
D9A4:
    {
        u8 *q = &g->c6B[idx];
        s32 saved = (s8)*q;
        r = 0xC0;
        r &= D_02021E90.c1470;
        if (r != 0xC0) {
            r = 0x40;
            r &= D_02021E90.c1470;
            if (r != 0) {
                if ((s8)*q > 1) *q = *q - 2;
            }
        }
        r = 0x80;
        r &= D_02021E90.c1470;
        if (r != 0) {
            s32 a1 = (s8)*q + 2;
            u8 lim = g->cF3[idx];
            if (a1 < lim) *q = *q + 2;
            else if (lim & 1) *q = lim - 1;
        }
        r = 0x30;
        r &= D_02021E90.c1470;
        if (r != 0x30 && r != 0) {
            u8 x = *q;
            *q = (x & 1) ? x - 1 : x + 1;
            if ((s8)*q == (s8)g->cF3[idx]) *q = *q - 1;
        }
        if (saved != (s8)*q) {
            sub_08005E80(0x139);
            sub_0800EDAC(0);
            sub_0800EF3C(g->c73[idx * 32 + (s8)*q]);
        }
        {
            u8 *rp = &g->c6F[idx];
            s32 dir = 0;
            u32 dv = *rp;
            if ((s8)*q < (s8)*rp) {
                dir = -1;
                dv = *rp - 2;
            } else {
                s32 df = (s8)*q - (s8)*rp;
                if (df > 7) {
                    dir = 1;
                    dv = *rp + 2;
                }
            }
            if (dir != 0) {
                *rp = dv;
                g->c69 = (g->c69 + 1) & 1;
                sub_0800F1D8((u8)g->c6A, g->c69);
                sub_0800F3C8(g->c69, 0);
            }
        }
    }
    v = D_02021E90.c146C;
    r = 2;
    r &= v;
    t = (u16)r;
    if (t != 0) {
        void **pp = &g->p48;
        void *obj = *pp;
        sub_08005E80(0x14F);
        if (obj != 0) sub_080C31E0(obj, *(void **)((u8 *)obj + 0x24));
        *pp = NULL;
        sub_0800EDAC(1);
        sub_0800EF3C(0xFF);
        {
            u8 *d = a + ((s16)*(u16 *)(a + 0x22) << 1);
            d[0x19] = 0;
        }
        sub_080C31E4(a + 0x18, a + 0x22, *(void **)&D_08671BC0);
        return;
    }
    r = 1;
    r &= v;
    if (r != 0) {
        u8 *d = a + ((s16)*(u16 *)(a + 0x22) << 1);
        d[0x19] = 0;
        sub_080C31E4(a + 0x18, a + 0x22, *(void **)&D_08671BB0);
    }
}
