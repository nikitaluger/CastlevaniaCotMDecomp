extern void *sub_0800355C(void);
extern s32 sub_0800168C(u8 *, s32, s32, unsigned int);
extern s32 sub_08013C2C(s32);
extern void sub_0801131C(u8 *, u8 *, s32);
extern void *sub_08016190(void);
extern void sub_08011368(u8 *, u8 *, s32, s32);
extern void sub_08053DCC(void);
extern void sub_08053DFC(u8 *, u8 *);
extern void sub_08016664(u8 *, s32);
extern s32 _call_via_r1(u8 *, s32);
extern s32 _call_via_r2(u8 *, u8 *, s32);
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
  s32 f18;
  s16 f1C;
  u8 _1E[4];
  s16 f22;
  u32 f24;
  struct E *f28;
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
  u8 _0[4];
  u16 f4;
  u16 f6;
  u8 _8[0x28 - 8];
};
extern struct TBL D_080CBDD0[];
extern s16 D_080CB2B8[];
extern u16 D_080CFAF4[];
extern u8 D_080CD400[];
inline static void set_f1c(struct P *p, s16 x)
{
  switch (x)
  {
    case 0x14C:
      p->f1C = 0x50;
      break;

    case 0x14D:
      p->f1C = 0x88;
      break;

    case 0x14E:
      p->f1C = 0x89;
      break;

  }

}

inline u8 *inline_fn(struct Arg0 *arg0)
{
  return ((u8 *) arg0) + 0x18;
}

void sub_080537AC(struct Arg0 *arg0)
{
  u8 *obj;
  struct P *r5;
  u8 *r9;
  s32 r0_3;
  u32 tmp;
  u32 zero;
  u32 zero2;
  u8 *base;
  s32 *fp;
  u8 *dat;
  s16 x;
  struct E *s;
  s16 *tbl8;
  volatile unsigned short pad;
  dat = *((u8 **) (((u8 *) arg0) + 0xAC));
  obj = sub_0800355C();
  r5 = NULL;
  s = NULL;
  r0_3 = 0;
  if ((((obj == NULL) || ((arg0->f38 = obj, sub_0800168C((u8 *) arg0, 0, 0x54, 0), r5 = arg0->f3C, r5 == NULL))) || ((r9 = ((u8 *) r5) + 0x34, r5->f24 = *((u32 *) (((u8 *) arg0) + 0x24)), *((u32 *) (((u8 *) arg0) + 0x24)) = (u32) sub_08053DCC, x = *((s16 *) ((*((u8 **) (dat + 4))) + 4)), (set_f1c(r5, x), 0), tbl8 = D_080CB2B8, r5->f18 = *((s16 *) ((((u8 *) tbl8) + (r5->f1C * 20)) + 2)), r5->f8 = ((s32) (*((s16 *) ((*((u8 **) (dat + 4))) + 0)))) << 16, r5->fC = ((s32) (*((s16 *) ((*((u8 **) (dat + 4))) + 2)))) << 16, r0_3 = sub_08013C2C(r5->f1C), zero = 0, r5->f22 = r0_3, ((s32) (r0_3 << 16)) < 0))) || ((sub_0801131C(obj, r9, ((s32) D_080CD400) + (r5->f1C * 0xC)), s = sub_08016190(), r5->f28 = s, s == NULL)))
  {
    _call_via_r1((u8 *) arg0, *((s32 *) (((u8 *) arg0) + 0x24)));
    return;
  }
  zero2 = 0;
  r5->f28->f1 = zero;
  r5->f28->f2 = 8;
  r5->f28->f3 = 1;
  r5->f28->f4 = *((u16 *) (((u8 *) tbl8) + (r5->f1C * 20)));
  r5->f28->f6 = D_080CFAF4[0];
  r5->f28->f8 = D_080CFAF4[1];
  r5->f28->fA = D_080CFAF4[2];
  r5->f28->fC = D_080CFAF4[3];
  r5->f28->fE = *((u16 *) ((((u8 *) tbl8) + (r5->f1C * 20)) + 4));
  r5->f28->f10 = (u32) obj;
  r5->f28->f14 = zero2;
  tmp = ((*((u16 *) obj)) & 0xC00) | ((((*((s16 *) (((u8 *) r5) + 0x22))) << 6) + 0x200) | (((*((u16 *) (((u8 *) r5) + 0x22))) + 8) << 12));
  *((u16 *) obj) = tmp;
  *((u16 *) obj) = tmp | D_02025FF0.f18C2;
  *((u32 *) (obj + 0x1C)) = 0x8000000E;
  base = (u8 *) (&D_02021E90);
  {
    u32 k = 0x1278;
    *((u32 *) (obj + 0x14)) = r5->f8 - (((*((u32 *) ((base + k) + ((D_02025FF0.f18A8 + 1) << 6)))) + 0x8000) & 0xFFFF0000);
  }
  {
    u32 k = 0x127C;
    *((u32 *) (obj + 0x18)) = r5->fC - (((*((u32 *) ((base + k) + ((D_02025FF0.f18A8 + 1) << 6)))) + 0xFFFF8000) & 0xFFFF0000);
  }
  *((u32 *) (r9 + 0x14)) = zero;
  sub_08011368(obj, r9, 0, 1);
  sub_08053DFC(obj, (u8 *) r5);
  sub_08016664((u8 *) arg0, 0);
  arg0->f2 |= 0x1000;
  *((u8 *) ((((u8 *) arg0) + (2 * arg0->f22)) + 0x19)) = zero;
  fp = (s32 *) 0x08671BB0;
  _call_via_r2(inline_fn(arg0), ((u8 *) arg0) + 0x22, *fp);
  *((u8 *) ((((u8 *) arg0) + (2 * arg0->f22)) + 0x19)) = (*((u8 *) ((((u8 *) arg0) + (2 * arg0->f22)) + 0x19))) + 1;
  {
    u8 *q = inline_fn(arg0) + (arg0->f22 * 2);
    _call_via_r1((u8 *) arg0, *((s32 *) ((((u8 *) arg0) + 0x14) + ((*((u8 *) q)) * 4))));
  }
}

