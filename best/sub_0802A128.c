extern void *sub_0800355C(void);
extern s32 sub_0800168C(u8 *, s32, s32, s32);
extern s32 sub_08013C2C(s32);
extern void sub_0801131C(u8 *, u8 *, s32);
extern void *sub_08016190(void);
extern void sub_08011368(u8 *, u8 *, s32, s32);
extern void sub_08016664(u8 *, s32);
extern s32 sub_08014938(s32);
extern void sub_0802A7A4(u8 *, void *);
extern s32 _call_via_r1(u8 *, s32);
extern s32 _call_via_r2(u8 *, u8 *, s32);
extern u32 *D_08671BB0;
extern u8 D_080CD400[];
struct E
{
  u8 _0;
  u8 f1;
  u8 f2;
  u8 f3;
  u16 f4;
  u16 f6;
  u16 f8;
  u16 fA;
  u16 fC;
  u16 fE;
  u32 f10;
  u16 f14;
};
struct P
{
  u8 _0[8];
  s32 f8;
  s32 fC;
  u32 f10;
  u32 f14;
  u32 f18;
  s16 f1C;
  u8 _1E[4];
  s16 f22;
  u32 f24;
  struct E *f28;
};
struct H
{
  u8 _0[4];
  s16 *f4;
};
struct Arg0
{
  u8 _0[2];
  u16 f2;
  u8 _4[0x22 - 4];
  s16 f22;
  u8 _24[0x38 - 0x24];
  u8 *f38;
  struct P *f3C;
  u8 _40[0x4C - 0x40];
  s16 f4C;
  u8 _4E[6];
  s16 f54;
  u8 _56[0x6C - 0x56];
  u16 f6C;
  u8 _6E[0xAC - 0x6E];
  struct H *fAC;
};
struct S_02025FF0
{
  u8 _0[0x18A8];
  u8 f18A8;
  u8 _18A9[0x19];
  u16 f18C2;
};
extern struct S_02025FF0 D_02025FF0;
struct S_02021E90
{
  u8 _0[0x1278];
  u32 f1278;
  u32 f127C;
};
extern struct S_02021E90 D_02021E90;
struct TBL
{
  u16 f0;
  s16 f2;
  u16 f4;
  u8 _6[0x14 - 6];
};
extern struct TBL D_080CB2B8[];
extern u16 D_080CE974[];
void sub_0802A128(struct Arg0 *arg0)
{
  struct H *e = arg0->fAC;
  u8 *obj;
  struct P *r5;
  u8 *r9;
  struct S_02025FF0 *new_var2;
  u8 *s;
  s32 tmp;
  short new_var;
  u32 zero;
  u32 zero2;
  u8 *base;
  s16 val;
  u32 new_var3;
  obj = sub_0800355C();
  r5 = NULL;
  s = NULL;
  tmp = 0;
  if ((((obj == NULL) || ((arg0->f38 = obj, sub_0800168C((u8 *) arg0, 0, 0x4C, 0), r5 = arg0->f3C, r5 == NULL))) || ((r9 = ((u8 *) r5) + 0x34, r5->f24 = *((u32 *) (((u8 *) arg0) + 0x24)), *((u32 *) (((u8 *) arg0) + 0x24)) = 0x0802A775, val = e->f4[2], (  {
    switch (val)
    {
      case 0xBB:
        r5->f1C = 1;
        break;

      case 0xBC:
        r5->f1C = 2;
        break;

      case 0xBD:
        r5->f1C = 3;
        break;

    }

    0;
  }
), r5->f18 = D_080CB2B8[r5->f1C].f2, r5->f8 = (*((s16 *) (((u8 *) arg0) + 0x4C))) << 16, r5->fC = (*((s16 *) (((u8 *) arg0) + 0x54))) << 16, tmp = sub_08013C2C(r5->f1C), zero2 = 0, zero = 0, r5->f22 = tmp, ((s32) (tmp << 16)) < 0))) || ((sub_0801131C(obj, r9, ((s32) D_080CD400) + (r5->f1C * 0xC)), s = sub_08016190(), r5->f28 = (struct E *) s, s == NULL)))
  {
    _call_via_r1((u8 *) arg0, *((s32 *) (((u8 *) arg0) + 0x24)));
    return;
  }
  r5->f28->f1 = zero;
  r5->f28->f2 = 8;
  r5->f28->f3 = 1;
  r5->f28->f4 = D_080CB2B8[r5->f1C].f0;
  r5->f28->f6 = D_080CE974[0];
  r5->f28->f8 = D_080CE974[1];
  r5->f28->fA = D_080CE974[2];
  r5->f28->fC = D_080CE974[3];
  r5->f28->fE = D_080CB2B8[r5->f1C].f4;
  r5->f28->f10 = (u32) obj;
  r5->f28->f14 = zero2;
  tmp = ((*((u16 *) obj)) & 0xC00) | ((((*((s16 *) (((u8 *) r5) + 0x22))) << 6) + 0x200) | (((*((u16 *) (((u8 *) r5) + 0x22))) + 8) << 12));
  new_var2 = &D_02025FF0;
  *((u16 *) obj) = tmp;
  *((u16 *) obj) = tmp | (*new_var2).f18C2;
  new_var3 = zero2;
  *((u32 *) (obj + 0x1C)) = 0x8000000A;
  base = (u8 *) (&D_02021E90);
  {
    u32 k = 0x1278;
    *((u32 *) (obj + 0x14)) = r5->f8 - (((*((u32 *) ((base + k) + ((D_02025FF0.f18A8 + 1) << 6)))) + 0x8000) & 0xFFFF0000);
  }
  {
    u32 k = 0x127C;
    *((u32 *) (obj + 0x18)) = r5->fC - (((*((u32 *) ((base + k) + (((*new_var2).f18A8 + 1) << 6)))) + 0xFFFF8000) & 0xFFFF0000);
  }
  *((u16 *) (((u8 *) r5) + 0x48)) = zero2;
  *((u16 *) (((u8 *) r5) + 0x4A)) = new_var3;
  sub_08011368(obj, r9, 0xD, 0);
  sub_0802A7A4(obj, r5);
  if (sub_08014938(r5->f8) > 0)
  {
    *((u16 *) (obj + 2)) |= 0x10;
  }
  sub_08016664((u8 *) arg0, 0);
  arg0->f2 |= 0x1000;
  *((u8 *) ((((u8 *) arg0) + (2 * arg0->f22)) + 0x19)) = zero;
  new_var = 0x18;
  {
    u32 *fp = (u32 *) 0x08671BB0;
    _call_via_r2(((u8 *) arg0) + 0x18, ((u8 *) arg0) + 0x22, *fp);
  }
  *((u8 *) ((((u8 *) arg0) + (2 * arg0->f22)) + 0x19)) = (*((u8 *) ((((u8 *) arg0) + (2 * arg0->f22)) + 0x19))) + 1;
  _call_via_r1((u8 *) arg0, *((u32 *) ((*((u32 *) (((u8 *) arg0) + 0x14))) + (4 * (*((u8 *) ((((u8 *) arg0) + new_var) + (tmp = 2 * arg0->f22))))))));
}

