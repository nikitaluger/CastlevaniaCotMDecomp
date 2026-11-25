extern void *sub_0800355C(void);
extern s32 sub_0800168C(u8 *, s32, s32, s32);
extern s32 sub_08013C2C(s32);
extern void sub_0801131C(u8 *, u8 *, s32);
extern void sub_08011368(u8 *, u8 *, s32, s32);
extern void *sub_08016190(void);
extern void sub_08016664(u8 *, s32);
extern void sub_080C31E4(u8 *, u8 *, s32);
extern s32 _call_via_r1(u8 *, s32);
extern void sub_0803EA3C(void);
extern u32 D_08671BB0;

struct E3E { u8 _0; u8 f1; u8 f2; u8 f3; u16 f4; u16 f6; u16 f8; u16 fA; u16 fC; u16 fE; u32 f10; u16 f14; };
struct P3E { u8 _0[8]; s32 f8; s32 fC; u8 _10[8]; u32 f18; s16 f1C; u8 _1E[4]; s16 f22; u32 f24; struct E3E *f28; u8 _2C[0x1C]; u16 f48; u16 f4A; u32 f4C; };
struct Arg3E { u8 _0[2]; u16 f2; u8 _4[0x10]; u32 f14; u8 _18[0xA]; s16 f22; u32 f24; u8 _28[0x10]; u8 *f38; struct P3E *f3C; u8 _40[0xC]; s16 f4C; u8 _4E[6]; s16 f54; u8 _56[6]; s16 f5C; };
struct S_02025FF0_3E { u8 _0[0x18A8]; u8 f18A8; u8 _18A9[0x19]; u16 f18C2; };
extern struct S_02025FF0_3E D_02025FF0;
struct S_02021E90_3E { u8 _0[0x1278]; u32 f1278; u32 f127C; };
extern struct S_02021E90_3E D_02021E90;
struct T3E_F4 { u16 f4; u16 f6; u16 fE; u8 _6[0xE]; };
extern u8 D_080CB2B8[];
extern u16 D_080CF42C[];
extern u8 D_080CD400[];

void sub_0803E5F4(struct Arg3E *arg0) {
    u32 zero;
    u32 zero2;
    u8 *obj;
    struct P3E *r5;
    u8 *r9;
    struct E3E *s;
    s32 r0_3;
    u32 tmp;
    u32 v32;
    u8 *r4;
    u8 *base;
    u8 *q0;
    u8 *q1;
    u32 *lit;
    s32 *base2;
    u32 idx;
    u16 *p48;

    obj = sub_0800355C();
    r5 = NULL;
    s = NULL;
    r0_3 = 0;
    if ((obj == NULL) ||
        (arg0->f38 = obj, sub_0800168C((u8 *)arg0, 0, 0x50, 0), r5 = arg0->f3C, r5 == NULL) ||
        (r9 = (u8 *)r5 + 0x34, r5->f24 = *(u32 *)((u8 *)arg0 + 0x24), *(u32 *)((u8 *)arg0 + 0x24) = (u32)sub_0803EA3C,
         zero2 = 0, zero = 0, r5->f1C = 0x57, r4 = (u8 *)&D_080CB2B8, r5->f18 = *(s16 *)((u8 *)r4 + r5->f1C * 0x14 + 2),
         r5->f8 = ((s16 *)((u8 *)arg0 + 0x4C))[0] << 16, r5->fC = ((s16 *)((u8 *)arg0 + 0x54))[0] << 16,
         r0_3 = sub_08013C2C(0x57), r5->f22 = (s16)r0_3, ((s32)(r0_3 << 16) < 0)) ||
        (sub_0801131C(obj, r9, (s32)D_080CD400 + r5->f1C * 0xC), s = (struct E3E *)sub_08016190(), r5->f28 = s, s == NULL)) {
        _call_via_r1((u8 *)arg0, *(s32 *)((u8 *)arg0 + 0x24));
        return;
    }
    r5->f28->f1 = (u8)zero;
    r5->f28->f2 = 8;
    r5->f28->f3 = 1;
    r5->f28->f4 = ((struct T3E_F4 *)r4)[r5->f1C].f4;
    r5->f28->f6 = D_080CF42C[0];
    r5->f28->f8 = D_080CF42C[1];
    r5->f28->fA = D_080CF42C[2];
    r5->f28->fC = D_080CF42C[3];
    r5->f28->fE = ((struct T3E_F4 *)r4)[r5->f1C].fE;
    r5->f28->f10 = (u32)obj;
    r5->f28->f14 = (u16)zero2;
    v32 = (*(u16 *)obj & 0xC00) |
          (((*(s16 *)((u8 *)r5 + 0x22) << 6) + 0x200) |
           ((*(u16 *)((u8 *)r5 + 0x22) + 8) << 12));
    *(u16 *)obj = v32;
    *(u16 *)obj = v32 | D_02025FF0.f18C2;
    *(u32 *)(obj + 0x1C) = 0x8000000A;
    base = (u8 *)&D_02021E90;
    { u32 k = 0x1278; *(u32 *)(obj + 0x14) = r5->f8 - ((*(u32 *)(base + k + ((D_02025FF0.f18A8 + 1) << 6)) + 0x8000) & 0xFFFF0000); }
    { u32 k = 0x127C; *(u32 *)(obj + 0x18) = r5->fC - ((*(u32 *)(base + k + ((D_02025FF0.f18A8 + 1) << 6)) + 0xFFFF8000) & 0xFFFF0000); }
    p48 = (u16 *)((u8 *)r5 + 0x48);
    p48[0] = 0x64;
    p48[1] = 0x0A;
    *(u32 *)(p48 + 2) = zero2;
    sub_08011368(obj, r9, 0, 1);
    if (((s16 *)((u8 *)arg0 + 0x5C))[0] > 0)
        *(u16 *)(obj + 2) = (u16)(*(u16 *)(obj + 2) | 0x10);
    sub_08016664((u8 *)arg0, 0);
    arg0->f2 |= 0x1000;
    q0 = (u8 *)(arg0->f22 * 2 + (u32)arg0);
    q0[0x19] = (u8)zero;
    lit = &D_08671BB0;
    r4 = (u8 *)arg0 + 0x18;
    sub_080C31E4(r4, (u8 *)arg0 + 0x22, *lit);
    q1 = (u8 *)(arg0->f22 * 2 + (u32)arg0);
    q1[0x19] = (u8)(q1[0x19] + 1);
    r4 += arg0->f22 * 2;
    idx = r4[0];
    base2 = *(s32 **)((u8 *)arg0 + 0x14);
    _call_via_r1((u8 *)arg0, base2[idx]);
}
