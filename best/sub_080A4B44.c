struct S_02025FF0 { u8 _0[0x18C2]; u16 w; };
extern struct S_02025FF0 D_02025FF0;
struct E { u8 _0, f1, f2, f3; u16 f4, f6, f8, fA, fC, fE; u32 f10; };
struct P {
    u8 _0[8]; u32 f8, fC; u8 _10[0xC]; u16 f1C; u8 _1E[4]; s16 f22; u8 _24[4];
    struct E *f28; u8 _2C[0x1C]; u32 f48;
};
struct Hdr { u16 f0; u16 f2; u16 f4; u16 f6; };
struct BD { u8 _0[0xC]; u16 fC; u16 fE; u8 _10[0x18]; };
extern struct BD D_080CBDD0[];
extern u16 D_08101CD4[];
extern void *D_08671BB0;
extern void *sub_0800355C(void);
extern void sub_0800168C(void *, s32, s32, s32);
extern void sub_08014288(void *, void *, void *);
extern s32 sub_08013C2C(s32);
extern void sub_0801131C(void *, void *, s32);
extern void sub_08011368(void *, void *, s32, s32);
extern void *sub_08016190(void);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, s32);
extern void sub_08097DC8(void);
inline int inline_fn(s32 arg0, int arg1) { return arg0 + arg1; }

void sub_080A4B44(u8 *arg0)
{
  s32 a; struct P *p; u8 *r7; u8 zero; u32 value; u16 *t; u8 *p18; void **fn; u8 *q;
  a = (s32) sub_0800355C();
  if (a == 0) goto fail;
  *((u32 *) (arg0 + 0x38)) = a;
  sub_0800168C(arg0, 0, 0x48, 0);
  if ((*((u32 *) (arg0 + 0x3C))) == 0) goto fail;
  *((u32 *) inline_fn(a, 0x1C)) = 0x8000000A;
  p = (struct P *) (*((u8 **) (arg0 + 0x3C)));
  r7 = ((u8 *) p) + 0x34;
  sub_08014288(arg0, (u8 *) p, sub_08097DC8);
  zero = 0;
  p->f1C = 0x59;
  p->f8 = *((u32 *) (arg0 + 0x4C));
  p->fC = *((u32 *) (arg0 + 0x5C));
  value = sub_08013C2C(0x59);
  p->f22 = value;
  if ((s16) value < 0) goto fail;
  value = p->f22;
  value = value << 6;
  value = value + 0x200;
  value &= 0xFC0;
  *((u16 *) a) = value;
  *((u16 *) a) |= D_02025FF0.w;
  sub_0801131C((void *) a, r7, inline_fn((*((s16 *) (((u8 *) p) + 0x1C))) * 0xC, 0x080CD400));
  sub_08011368((void *) a, r7, 4, 0);
  *((u8 *) (arg0 + 0x8C)) = 2;
  ((struct Hdr *) a)->f4 = 0x400;
  ((struct Hdr *) a)->f6 = 0x80;
  t = D_08101CD4;
  p->f28 = (struct E *) sub_08016190();
  if (p->f28 != NULL) goto cont;
  fail:
  sub_080C31E0(arg0, *((void **) (arg0 + 0x24)));
  return;
  cont:
  p->f28->f1 = zero;
  p->f28->f2 = 8;
  p->f28->f3 = 1;
  p->f28->f4 = D_080CBDD0[*((s16 *) (((u8 *) p) + 0x1C))].fC;
  p->f28->f6 = t[0];
  p->f28->f8 = t[1];
  p->f28->fA = t[2];
  p->f28->fC = t[3];
  p->f28->fE = D_080CBDD0[*((s16 *) (((u8 *) p) + 0x1C))].fE;
  p->f28->f10 = a;
  *((u16 *) (arg0 + 2)) |= 0x1000;
  *((u8 *) inline_fn(inline_fn(((u32) (*((s16 *) (arg0 + 0x22)))) * 2, (u32) arg0), 0x19)) = zero;
  fn = &D_08671BB0;
  p18 = arg0;
  p18 += 0x18;
  sub_080C31E4(p18, arg0 + 0x22, (s32) (*fn));
  *((u8 *) inline_fn(inline_fn(((u32) (*((s16 *) (arg0 + 0x22)))) * 2, (u32) arg0), 0x19)) += 1;
  q = p18 + (((u32) (*((s16 *) (arg0 + 0x22)))) * 2);
  sub_080C31E0(arg0, *((void **) ((*((u8 **) (arg0 + 0x14))) + ((*((u8 *) q)) * 4))));
}
