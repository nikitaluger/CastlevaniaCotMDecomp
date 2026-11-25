extern void *sub_0800355C(void);
extern s32 sub_0800168C(u8 *, s32, s32, s32);
extern void sub_08014288(u8 *, u8 *, void *);
extern void sub_08097D18(u8 *, u8 *, u8 *, void *, s32);
extern void sub_0809C2F0(u8 *, u8 *, s32, s32);
extern void sub_080114DC(u8 *, u8 *, s32, s32);
extern void sub_08097EB4(void *);
extern void *sub_08016190(void);
extern void sub_0809C618(s32, u8 *, void *);
extern void sub_080036C0(s32);
extern void sub_08097F70(void *, s32);
extern s32 sub_0805FAEC(void *, s32);
extern void sub_0809C318(s32, u8 *, u8 *, u8 *, s32);
extern void sub_0809C3F4(u8 *, u8 *, u8 *, u8 *);
extern void sub_0809C490(s32, u8 *, u8 *, u8 *);
extern void sub_08016664(u8 *, s32);
extern void sub_080992DC(void);
extern void sub_080C31E0(u8 *, s32);
extern void sub_080C31E4(u8 *, u8 *, s32);
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
};
struct Arg0
{
  u8 _0[2];
  u16 f2;
  u8 _4[0x14 - 4];
  u8 *f14;
  u8 f18[10];
  s16 f22;
  u8 _24[0x38 - 0x24];
  u8 *f38;
  u8 *f3C;
  u8 _40[0xAC - 0x40];
  void *fAC;
};
struct TBL3
{
  u16 f0;
  s16 f2;
  u16 f4;
  u8 _6[0x14 - 6];
};
extern struct TBL3 D_080CB2B8[];
extern u16 D_081017AC[];
extern u8 D_083C6A04[];
extern u8 D_083CE604[];
struct S_02025FF0
{
  u8 _0[0x1870];
  u32 v;
};
extern struct S_02025FF0 D_02025FF0;
void sub_080989BC(struct Arg0 *arg0)
{
  u8 *obj;
  u8 *p;
  u8 *r9;
  u8 *r6;
  void *h;
  s32 tmp;
  int new_var;
  volatile u16 sp4;
  u16 *data;
  u8 *base;
  h = arg0->fAC;
  obj = sub_0800355C();
  if (obj == NULL)
  {
    goto fail;
  }
  arg0->f38 = obj;
  sub_0800168C((u8 *) arg0, 0, 0x70, 0);
  if ((*((u32 *) (((u8 *) arg0) + 0x3C))) == 0)
  {
    goto fail;
  }
  *((u32 *) (obj + 0x1C)) = 4;
  p = arg0->f3C;
  r9 = p + 0x34;
  r6 = p + 0x48;
  sub_08014288((u8 *) arg0, p, (void *) sub_080992DC);
  sub_08097D18((u8 *) arg0, obj, p, h, 0x44);
  sub_0809C2F0(obj, r9, 0x38, 0x0C);
  sub_080114DC(obj, r9, 0, 1);
  sub_08097EB4(D_083C6A04);
  {
    u16 v = *((u16 *) (p + 4));
    sp4 = 0;
    *((u16 *) (p + 4)) = v | 0x10;
  }
  data = D_081017AC;
  *((void **) (p + 0x28)) = sub_08016190();
  if ((*((void **) (p + 0x28))) == NULL)
  {
    goto fail;
  }
  ((struct E *) (*((void **) (p + 0x28))))->f1 = 5;
  ((struct E *) (*((void **) (p + 0x28))))->f2 = 8;
  ((struct E *) (*((void **) (p + 0x28))))->f3 = 1;
  ((struct E *) (*((void **) (p + 0x28))))->f4 = D_080CB2B8[*((s16 *) (p + 0x1C))].f0;
  ((struct E *) (*((void **) (p + 0x28))))->f6 = data[0];
  ((struct E *) (*((void **) (p + 0x28))))->f8 = data[1];
  ((struct E *) (*((void **) (p + 0x28))))->fA = data[2];
  ((struct E *) (*((void **) (p + 0x28))))->fC = data[3];
  ((struct E *) (*((void **) (p + 0x28))))->fE = D_080CB2B8[*((s16 *) (p + 0x1C))].f4;
  ((struct E *) (*((void **) (p + 0x28))))->f10 = (u32) obj;
  *((void **) (p + 0x48)) = sub_08016190();
  if ((*((void **) (p + 0x48))) == NULL)
  {
    goto fail;
  }
  ((struct E *) (*((void **) (p + 0x48))))->f1 = 5;
  ((struct E *) (*((void **) (p + 0x48))))->f2 = 8;
  ((struct E *) (*((void **) (p + 0x48))))->f3 = 1;
  ((struct E *) (*((void **) (p + 0x48))))->f4 = D_080CB2B8[*((s16 *) (p + 0x1C))].f0;
  ((struct E *) (*((void **) (p + 0x48))))->f6 = data[0];
  ((struct E *) (*((void **) (p + 0x48))))->f8 = data[1];
  ((struct E *) (*((void **) (p + 0x48))))->fA = data[2];
  new_var = 4;
  ((struct E *) (*((void **) (p + 0x48))))->fC = data[3];
  ((struct E *) (*((void **) (p + 0x48))))->fE = D_080CB2B8[*((s16 *) (p + 0x1C))].f4;
  ((struct E *) (*((void **) (p + 0x48))))->f10 = (u32) obj;
  *((void **) (r6 + 4)) = sub_08016190();
  if ((*((void **) (r6 + new_var))) != NULL)
  {
    goto body;
  }
  fail:
  sub_080C31E0((u8 *) arg0, *((s32 *) (((u8 *) arg0) + 0x24)));

  goto end;
  body:
  ((struct E *) (*((void **) (r6 + new_var))))->f1 = 5;

  ((struct E *) (*((void **) (r6 + new_var))))->f2 = 8;
  ((struct E *) (*((void **) (r6 + 4))))->f3 = 1;
  ((struct E *) (*((void **) (r6 + 4))))->f4 = D_080CB2B8[*((s16 *) (p + 0x1C))].f0;
  ((struct E *) (*((void **) (r6 + new_var))))->f6 = data[0];
  ((struct E *) (*((void **) (r6 + 4))))->f8 = data[1];
  ((struct E *) (*((void **) (r6 + 4))))->fA = data[2];
  ((struct E *) (*((void **) (r6 + 4))))->fC = data[3];
  ((struct E *) (*((void **) (r6 + new_var))))->fE = D_080CB2B8[*((s16 *) (p + 0x1C))].f4;
  ((struct E *) (*((void **) (r6 + new_var))))->f10 = (u32) obj;
  sub_0809C618(0, r9, *((void **) (p + 0x28)));
  sub_0809C618(1, r9, *((void **) (p + 0x48)));
  sub_0809C618(2, r9, *((void **) (r6 + 4)));
  sub_080036C0(0xA);
  sub_08097F70(D_083CE604, 3);
  *((s32 *) (r6 + 8)) = sub_0805FAEC(arg0, 0x17A);
  sub_0809C318(*((s32 *) (r6 + 8)), obj, p, r9, *((u16 *) (r6 + 0x24)));
  *((s32 *) (r6 + 0xC)) = sub_0805FAEC(arg0, 0x17B);
  *((s32 *) (r6 + 0x10)) = sub_0805FAEC(arg0, 0x17C);
  sub_0809C3F4(p + 0x54, obj, p, r9);
  tmp = sub_0805FAEC(arg0, 0x175);
  *((s32 *) (r6 + 0x14)) = tmp;
  sub_0809C490(tmp, obj, p, r9);
  *((s32 *) (r6 + 0x18)) = sub_0805FAEC((void *) D_02025FF0.v, 0x176);
  sub_08016664((u8 *) arg0, 0);
  arg0->f2 |= 0x1000;
  *((u8 *) ((((u8 *) arg0) + (2 * arg0->f22)) + 0x19)) = *((u8 *) (&sp4));
  base = ((u8 *) arg0) + 0x18;
  sub_080C31E4(base, ((u8 *) arg0) + 0x22, *((s32 *) 0x08671BB0));
  *((u8 *) ((((u8 *) arg0) + (2 * arg0->f22)) + 0x19)) += 1;
  sub_080C31E0((u8 *) arg0, *((s32 *) (arg0->f14 + (base[2 * arg0->f22] * 4))));
  end:
  return;

}

