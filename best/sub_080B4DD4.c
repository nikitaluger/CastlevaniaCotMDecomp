extern s32 sub_0800168C(void *, s32, s32, s32);
extern void *sub_0800355C(void);
extern s32 sub_080114DC(void *, s32, s32, s32);
extern s32 sub_08013C2C(void);
extern s32 sub_08014288(void *, void *, void *);
extern void *sub_08016190(void);
extern s32 sub_080B710C(void *, s32, s32, s32);
extern s32 sub_080C31E0(void *, s32);
extern s32 sub_080C31E4(void *, void *, s32);
extern s32 sub_08097D90;
extern s32 D_08671BB0;
struct D02025FF0
{
  u8 _0[0x18C2];
  u16 w;
};
extern struct D02025FF0 D_02025FF0;
struct Obj6
{
  u16 f0;
  u16 f2;
  u8 _4[0x1C - 0x4];
  u32 f1C;
};
struct Obj4
{
  u8 _0[0x1C];
  u16 f1C;
  u8 _1[0x22 - 0x1E];
  u16 f22;
  u8 _2[0x28 - 0x24];
  void *f28;
};
struct Obj28
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
};
struct Arg0
{
  u8 _0[0x02];
  u16 f2;
  u8 _1[0x14 - 0x04];
  void *f14;
  u8 _2[0x22 - 0x18];
  s16 f22;
  void *f24;
  u8 _4[0x38 - 0x28];
  void *f38;
  void *f3C;
  u8 _5[0x5C - 0x40];
  s32 f5C;
};
struct Table2Ent
{
  u8 _0[4];
  u16 f4;
  u16 f6;
  u8 _8[0x28 - 0x8];
};
extern struct Table2Ent D_080CBDD0[];
inline int inline_fn(s16 arg0)
{
  return arg0 * 2;
}

void sub_080B4DD4(void *arg0)
{
  int new_var9;
  struct Arg0 *a = arg0;
  s16 new_var;
  struct Obj6 *o6;
  struct Obj4 *o4;
  struct Obj28 *o28;
  struct Arg0 **new_var6[2];
  struct Arg0 **new_var10;
  int new_var2;
  s16 new_var4;
  u8 *p34;
  u8 *p18;
  s16 new_var11;
  void *new_var8;
  struct Arg0 **(*new_var7)[2];
  u16 *t1;
  void *new_var3;
  s32 v;
  s16 idx;
  unsigned long b;
  void *p;
  u8 *new_var5;
  o6 = sub_0800355C();
  if (o6 == NULL)
  {
    goto fail;
    new_var2 = sub_08013C2C();
  }
  a->f38 = o6;
  D_02025FF0.w += 0;
  sub_0800168C(arg0, 0, 0x48, 0);
  if (a->f3C == NULL)
  {
  }
  goto fail;
  o6->f1C = 0x80000009;
  o4 = a->f3C;
  p34 = ((u8 *) o4) + 0x34;
  sub_08014288(new_var8 = arg0, o4, &sub_08097D90);
  o4->f1C = 0x66;
  v = new_var2;
  new_var3 = a->f14;
  o4->f22 = v;
  if (((v << 7) << 9) < 0)
  {
    goto fail;
  }
  new_var2 = a->f5C;
  new_var2 = new_var2 > 0;
  if (new_var2)
  {
  }
  sub_080B710C(o6, p34, 0x50, 3);
  sub_080114DC(o6, p34, 0x70, 0);
  t1 = (u16 *) 0x08102B84;
  new_var7 = &new_var6;
  o4->f28 = o28;
  D_080CBDD0[idx].f4 = D_080CBDD0[idx].f4;
  if (o28 == NULL)
  {
    new_var6[1] = &a;
    fail:
    sub_080C31E0(new_var8, (*(*new_var7)[1])->f24);

    o6->f2 |= 0x10;
    o28 = sub_08016190();
    goto end;
  }
  o28->f1 = 1;
  o28->f2 = 8;
  o28->f3 = 1;
  idx = o4->f1C;
  o28->f4 = D_080CBDD0[idx].f4;
  new_var9 = 0x19;
  o28->f6 = t1[0];
  new_var11 = (*new_var6[0])->f22;
  o28->f8 = t1[1];
  o28->fA = t1[2];
  o28->fC = t1[3];
  o28->fE = D_080CBDD0[idx].f6;
  new_var6[0] = &(*new_var6[1]);
  o28->f10 = o6;
  o6->f2 |= 0x400;
  (*new_var6[1])->f2 |= 0x1000;
  idx = new_var11;
  *((u8 *) ((((u8 *) new_var8) + (idx * 2)) + 0x19)) = 0;
  p18 = (u8 *) new_var8;
  p18 = p18 + 0x18;
  sub_080C31E4(p18, ((u8 *) new_var8) + 0x22, D_08671BB0);
  idx = a->f22;
  *((u8 *) ((((u8 *) new_var8) + inline_fn(idx)) + new_var9)) += 1;
  new_var4 = a->f22;
  new_var = new_var4;
  idx = new_var;
  new_var10 = new_var6[0];
  b = *((((u8 *) new_var8) + 0x18) + (idx * 2));
  p = (void *) (((u8 *) new_var3) + (b * 4));
  new_var5 = &b;
  sub_080C31E0(new_var8, *((s32 *) ((void *) (((u8 *) (*new_var10)->f14) + ((*new_var5) * 4)))));
  end:
  ;

  ;
  ;
  ;
  ;
  ;
  o6->f0 = o6->f0 | D_02025FF0.w;
  ;
  ;
  ;
  ;
  ;
  ;
}

