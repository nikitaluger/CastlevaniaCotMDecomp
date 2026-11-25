extern void sub_08003A6C(void *, s32, void *);
extern void *sub_08016190(void);
extern void sub_0806D2D0(void *);
extern s16 sub_0806D62C(u16, s32);
extern void sub_080722E0(void *, u8);
extern void sub_0808449C(void);
extern void sub_080C31E0(void *, s32);
extern void sub_080C31E4(void *, void *, s32);
extern u8 D_02025368[];
extern u32 D_084E574C;
extern u32 D_084E57B4;
extern s32 D_08671BB0;

struct S_7D114 {
    u8 _0[0x2C];
    u8 *volatile res;
};

struct S_FF0 {
    u8 _0[0x1510];
    u8 b1510;
};
extern struct S_FF0 D_02025FF0;

void sub_0807D114(u8 *arg0)
{
    s32 z;
    s32 zero;
    u32 c;
    u8 *p68 = *(u8 **)(arg0 + 0x6C);
    u8 *r7 = p68 + 4;
    u8 *rp = *(u8 **)(arg0 + 0x38);
    u8 *base2 = D_02025368;
    void *res;
    struct S_7D114 *s = (struct S_7D114 *)r7;

    res = sub_08016190();
    s->res = res;
    if (res == NULL) {
        sub_0806D2D0(arg0);
        return;
    }
    z = 0;
    *(u32 *)(r7 + 0x30) = z;
    *(u32 *)(r7 + 0x34) = z;
    *(u32 *)(r7 + 0x38) = z;
    *(u32 *)(r7 + 0x3C) = z;
    *(u8 *)(res + 1) = 1 & D_02025FF0.b1510;
    *(u8 *)(s->res + 2) = 2;
    *(u8 *)(s->res + 3) = 8;
    *(u16 *)(s->res + 4) = *(u8 *)(base2 + 0x304);
    zero = 0;
    *(u16 *)(s->res + 6) = 10;
    *(u16 *)(s->res + 8) = 10;
    *(u16 *)(s->res + 0xA) = zero;
    *(u16 *)(s->res + 0xC) = zero;
    *(u16 *)(s->res + 0xE) = sub_0806D62C(*(u16 *)(base2 + 0x2E2), 0x57);
    *(u16 *)(s->res + 0x16) = 0x1E;
    *(u16 *)(s->res + 0x18) = 0x62;
    {
        u8 *rr = s->res;
        *(void **)(rr + 0x10) = rp;
    }
    *(u32 *)(r7 + 0x18) = *(u32 *)(arg0 + 0x24);
    *(u32 *)(arg0 + 0x24) = (u32)&sub_0808449C;
    *(u32 *)(rp + 0x24) = (u32)&D_084E574C;
    sub_08003A6C(p68 + 0x20, 0, &D_084E57B4);
    ((s32 *)p68)[1] = *(s32 *)0x02027718;
    *(s32 *)(r7 + 4) = *(s32 *)0x0202771C + 0xFF800000;
    *(u32 *)(r7 + 0x10) = zero;
    c = 0x80 << 7;
    *(u32 *)(r7 + 0x40) = c;
    p68[0x48] = 0x40;
    p68[0x49] = 4;
    sub_080722E0(r7, p68[0x48]);
    *(u32 *)(r7 + 0x54) = 0x80;
    *(u8 *)(arg0 + *(s16 *)(arg0 + 0x22) * 2 + 0x19) = zero;
    {
        s32 *g;
        g = (s32 *)0x08671BB0;
        sub_080C31E4(arg0 + 0x18, arg0 + 0x22, *g);
    }
    *(u8 *)(arg0 + *(s16 *)(arg0 + 0x22) * 2 + 0x19) = *(u8 *)(arg0 + *(s16 *)(arg0 + 0x22) * 2 + 0x19) + 1;
    {
        s32 idx;
        u8 *base;
        base = arg0 + 0x18;
        idx = *(s16 *)(arg0 + 0x22) * 2;
        base += idx;
        sub_080C31E0(arg0, *(s32 *)(*(u8 *)base * 4 + *(u32 *)(arg0 + 0x14)));
    }
}
