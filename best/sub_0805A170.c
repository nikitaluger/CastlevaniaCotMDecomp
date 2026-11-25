extern void *sub_0800355C(void);
extern s32 sub_0800168C(u8 *, s32, s32, s32);
extern s32 sub_08013C2C(s32);
extern void sub_0801131C(u8 *, u8 *, s32);
extern void *sub_08016190(void);
extern void sub_08011368(u8 *, u8 *, s32, s32);
extern void sub_08016664(u8 *, s32);
extern s32 sub_08005910(s32, s32);
extern void sub_0805A85C(void);
extern void sub_080C31E0(void *, u32);
extern void sub_080C31E4(void *, void *, s32);

struct E { u8 _0; u8 f1; u8 f2; u8 f3; u16 f4; u16 f6; u16 f8; u16 fA; u16 fC; u16 fE; u32 f10; u16 f14; };
struct P { u8 _0[8]; s32 f8; s32 fC; u32 f10; u32 f14; u32 f18; s16 f1C; u8 _1E[4]; s16 f22; u32 f24; struct E *f28; };
struct Ref { s16 f0; s16 f2; };
struct RefHolder { u8 _0[4]; struct Ref *f4; };
struct Arg0 { u8 _0[2]; u16 f2; u8 _4[0x22-4]; s16 f22; u8 _24[0x38-0x24]; u8 *f38; struct P *f3C; u8 _40[0x4C-0x40]; s16 f4C; u8 _4E[6]; s16 f54; u8 _56[0xAC-0x56]; struct RefHolder *fAC; };
struct S_02025FF0 { u8 _0[0x18A8]; u8 f18A8; u8 _18A9[0x19]; u16 f18C2; };
extern struct S_02025FF0 D_02025FF0;
struct S_02021E90 { u8 _0[0x1278]; u32 f1278; u32 f127C; };
extern struct S_02021E90 D_02021E90;
struct TBL3 { u16 f0; s16 f2; u16 f4; u8 _6[0x14-6]; };
extern struct TBL3 D_080CB2B8[];
extern u16 D_080CFDCC[];
extern u8 D_080CD400[];

void sub_0805A170(struct Arg0 *arg0) {
    u8 *obj;
    struct P *r6;
    u8 *r10;
    u8 *s;
    s32 r0_3;
    u32 tmp;
    u32 zero;
    u8 *base;
    u8 *tbl;
    s32 *fp;
    struct RefHolder *h;
    s32 idx;

    h = arg0->fAC;
    obj = sub_0800355C();
    r6 = NULL;
    s = NULL;
    r0_3 = 0;
    if ((obj == NULL) ||
        (arg0->f38 = obj, sub_0800168C((u8 *)arg0, 0, 0x88, 0), r6 = arg0->f3C, r6 == NULL) ||
        (r10 = (u8 *)r6 + 0x34, r6->f24 = *(u32 *)((u8 *)arg0 + 0x24), *(u32 *)((u8 *)arg0 + 0x24) = (u32)sub_0805A85C,
         zero = 0, r6->f1C = 0x52,
         tbl = (u8 *)D_080CB2B8,
         idx = r6->f1C, r6->f18 = ((struct TBL3 *)tbl)[idx].f2,
         r6->f8 = h->f4->f0 << 16, r6->fC = h->f4->f2 << 16,
         r0_3 = sub_08013C2C(0x52), r6->f22 = r0_3, ((s32)(r0_3 << 16) < 0)) ||
        (sub_0801131C(obj, r10, (s32)D_080CD400 + r6->f1C * 0xC), s = sub_08016190(), r6->f28 = (struct E *)s, s == NULL)) {
        sub_080C31E0((u8 *)arg0, *(s32 *)((u8 *)arg0 + 0x24));
        return;
    }
    r6->f28->f1 = 0;
    r6->f28->f2 = 8;
    r6->f28->f3 = 1;
    r6->f28->f4 = ((struct TBL3 *)tbl)[r6->f1C].f0;
    r6->f28->f6 = D_080CFDCC[0];
    r6->f28->f8 = D_080CFDCC[1];
    r6->f28->fA = D_080CFDCC[2];
    r6->f28->fC = D_080CFDCC[3];
    r6->f28->fE = ((struct TBL3 *)tbl)[r6->f1C].f4;
    r6->f28->f10 = (u32)obj;
    r6->f28->f14 = zero;
    tmp = (*(u16 *)obj & 0xC00) |
          (((*(s16 *)((u8 *)r6 + 0x22) << 6) + 0x200) |
           ((*(u16 *)((u8 *)r6 + 0x22) + 8) << 12));
    *(u16 *)obj = tmp;
    *(u16 *)obj = tmp | D_02025FF0.f18C2;
    *(u32 *)(obj + 0x1C) = 0x8000000A;
    base = (u8 *)&D_02021E90;
    { u32 k = 0x1278; *(u32 *)(obj + 0x14) = r6->f8 - ((*(u32 *)(base + k + ((D_02025FF0.f18A8 + 1) << 6)) + 0x8000) & 0xFFFF0000); }
    { u32 k = 0x127C; *(u32 *)(obj + 0x18) = r6->fC - ((*(u32 *)(base + k + ((D_02025FF0.f18A8 + 1) << 6)) + 0xFFFF8000) & 0xFFFF0000); }
    {
        u8 *p = (u8 *)r6 + 0x48;
        *(u16 *)(p + 0x0A) = zero;
        *(u16 *)(p + 8) = zero;
    }
    {
        s32 r = sub_08005910(*(s32 *)((u8 *)&D_02025FF0 + 0x1750) - r6->fC,
                             *(s32 *)((u8 *)&D_02025FF0 + 0x174C) - r6->f8);
        u8 *p = (u8 *)r6 + 0x5C;
        *(u32 *)((u8 *)r6 + 0x5C) = 0x6000;
        *(u32 *)(p + 4) = r;
        *(u32 *)(p + 8) = 0x6000;
        *(u32 *)(p + 0x0C) = 0x6000;
        *(u32 *)(p + 0x10) = 0;
        *(u32 *)(p + 0x14) = 0x200;
        *(u32 *)(p + 0x1C) = 0;
        *(u16 *)(p + 0x1A) = 0;
    }
    sub_08011368(obj, r10, 0, 1);
    sub_08016664((u8 *)arg0, 0);
    arg0->f2 |= 0x1000;
    *(u8 *)((u8 *)arg0 + 2 * arg0->f22 + 0x19) = 0;
    {
        u8 *p18;
        s32 *lit;
        lit = (s32 *)0x08671BB0;
        p18 = (u8 *)arg0 + 0x18;
        sub_080C31E4(p18, (u8 *)arg0 + 0x22, *lit);
        *(u8 *)((u8 *)arg0 + 2 * arg0->f22 + 0x19) = *(u8 *)((u8 *)arg0 + 2 * arg0->f22 + 0x19) + 1;
        p18 = p18 + 2 * arg0->f22;
        sub_080C31E0((u8 *)arg0, *(u32 *)(*(u32 *)((u8 *)arg0 + 0x14) + 4 * *(u8 *)p18));
    }
}
