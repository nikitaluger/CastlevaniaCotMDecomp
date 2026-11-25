extern void *sub_0800355C(void);
extern s32 sub_0800168C(u8 *, s32, s32, s32);
extern s32 sub_08013C2C(s32);
extern void sub_0801131C(u8 *, u8 *, s32);
extern void *sub_08016190(void);
extern void sub_08011368(u8 *, u8 *, s32, s32);
extern void sub_08016664(u8 *, s32);
extern void sub_080149A4(u8 *, u8 *, u8 *, s32, s32);
extern void sub_0803E460(void);
extern void sub_0803E4A8(u8 *, u8 *);
extern void sub_080C31E0(u8 *, s32);
extern void sub_080C31E4(u8 *, u8 *, s32);

struct E { u8 _0; u8 f1; u8 f2; u8 f3; u16 f4; u16 f6; u16 f8; u16 fA; u16 fC; u16 fE; u32 f10; u16 f14; };
struct P { u8 _0[4]; u16 f4; u8 _6[2]; s32 f8; s32 fC; u8 _10[8]; s32 f18; s16 f1C; u8 _1E[4]; s16 f22; u32 f24; struct E *f28; u8 _2C[0x1C]; u16 f48; u8 _4A[2]; struct E *f4C[2]; };
struct Ref { s16 f0; s16 f2; };
struct RefHolder { u8 _0[4]; struct Ref *f4; };
struct Arg0 { u8 _0[2]; u16 f2; u8 _4[0x14-4]; u8 *f14; u8 f18[10]; s16 f22; u8 _24[0x38-0x24]; u8 *f38; struct P *f3C; u8 _40[0xAC-0x40]; struct RefHolder *fAC; };

struct S_02025FF0 { u8 _0[0x18A8]; u8 f18A8; u8 _18A9[0x19]; u16 f18C2; };
extern struct S_02025FF0 D_02025FF0;
struct S_02021E90 { u8 _0[0x1278]; u32 f1278; u32 f127C; };
extern struct S_02021E90 D_02021E90;
struct TBL3 { u16 f0; s16 f2; u16 f4; u8 _6[0x14-6]; };
extern struct TBL3 D_080CB2B8[];
extern u16 D_080CF3DC[];
extern u16 D_080CF3FC[];
extern u8 D_080CD400[];
struct TBL28 { u8 _0[4]; u16 f4; u16 f6; u8 _8[0x28-8]; };
extern struct TBL28 D_080CBDD0[];

void sub_0803DECC(struct Arg0 *arg0) {
    u8 *obj;
    struct P *r5;
    u8 *sp4;
    u8 *s;
    s32 r0_3;
    u32 tmp;
    u32 zero;
    u8 *base;
    s32 *fp;
    u8 *p18;
    struct RefHolder *h;
    s32 i;

    h = arg0->fAC;
    obj = sub_0800355C();
    r5 = NULL;
    s = NULL;
    r0_3 = 0;
    if ((obj == NULL) ||
        (arg0->f38 = obj, sub_0800168C((u8 *)arg0, 0, 0x54, 0), r5 = arg0->f3C, r5 == NULL) ||
        (sp4 = (u8 *)r5 + 0x34, r5->f24 = *(u32 *)((u8 *)arg0 + 0x24), *(u32 *)((u8 *)arg0 + 0x24) = (u32)sub_0803E460,
         zero = 0, r5->f1C = 0x61,
         r5->f18 = D_080CB2B8[r5->f1C].f2,
         r5->f8 = h->f4->f0 << 16, r5->fC = h->f4->f2 << 16,
         r0_3 = sub_08013C2C(0x61), r5->f22 = r0_3, ((s32)(r0_3 << 16) < 0)) ||
        (sub_0801131C(obj, sp4, (s32)D_080CD400 + r5->f1C * 0xC), s = sub_08016190(), r5->f28 = (struct E *)s, s == NULL)) {
        sub_080C31E0((u8 *)arg0, *(s32 *)((u8 *)arg0 + 0x24));
        return;
    }
    r5->f28->f1 = 0;
    r5->f28->f2 = 8;
    r5->f28->f3 = 1;
    r5->f28->f4 = D_080CB2B8[r5->f1C].f0;
    r5->f28->f6 = D_080CF3DC[0];
    r5->f28->f8 = D_080CF3DC[1];
    r5->f28->fA = D_080CF3DC[2];
    r5->f28->fC = D_080CF3DC[3];
    r5->f28->fE = D_080CB2B8[r5->f1C].f4;
    r5->f28->f10 = (u32)obj;
    r5->f28->f14 = zero;
    tmp = (*(u16 *)obj & 0xC00) |
          (((*(s16 *)((u8 *)r5 + 0x22) << 6) + 0x200) |
           ((*(u16 *)((u8 *)r5 + 0x22) + 8) << 12));
    *(u16 *)obj = tmp;
    *(u16 *)obj = tmp | D_02025FF0.f18C2;
    *(u32 *)(obj + 0x1C) = 0x8000000A;
    base = (u8 *)&D_02021E90;
    *(u32 *)(obj + 0x14) = r5->f8 - ((*(u32 *)(base + 0x1278 + ((D_02025FF0.f18A8 + 1) << 6)) + 0x8000) & 0xFFFF0000);
    *(u32 *)(obj + 0x18) = r5->fC - ((*(u32 *)(base + 0x127C + ((D_02025FF0.f18A8 + 1) << 6)) + 0xFFFF8000) & 0xFFFF0000);
    r5->f48 = zero;
    for (i = 0; i < 2; i++) {
        struct E *e = sub_08016190();
        r5->f4C[i] = e;
        if (e == NULL) {
            sub_080C31E0((u8 *)arg0, *(s32 *)((u8 *)arg0 + 0x24));
            return;
        }
        e->f1 = 0;
        e->f2 = 8;
        e->f3 = 1;
        e->f4 = D_080CBDD0[r5->f1C].f4;
        e->f6 = D_080CF3FC[i * 4 + 0];
        e->f8 = D_080CF3FC[i * 4 + 1];
        e->fA = D_080CF3FC[i * 4 + 2];
        e->fC = D_080CF3FC[i * 4 + 3];
        e->fE = D_080CBDD0[r5->f1C].f6;
        e->f10 = (u32)obj;
        e->f14 = 0;
    }
    sub_080149A4(obj, (u8 *)r5, (u8 *)r5 + 0x48, 0x78, 0xF0);
    r5->f4 = 8;
    sub_08011368(obj, sp4, 0, 1);
    sub_0803E4A8((u8 *)arg0, obj);
    sub_08016664((u8 *)arg0, 0);
    arg0->f2 |= 0x1000;
    *(u8 *)((u8 *)arg0 + 2 * arg0->f22 + 0x19) = 0;
    fp = (s32 *)0x08671BB0;
    p18 = (u8 *)arg0 + 0x18;
    sub_080C31E4(p18, (u8 *)arg0 + 0x22, *fp);
    {
        u8 *p = (u8 *)arg0 + 2 * arg0->f22;
        p[0x19] = p[0x19] + 1;
    }
    sub_080C31E0((u8 *)arg0, *(s32 *)(arg0->f14 + *(u8 *)(p18 + 2 * arg0->f22) * 4));
}
