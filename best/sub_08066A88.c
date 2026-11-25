struct A66
{
  u8 _0[0x22];
  s16 unk22;
  u8 _24[0x14];
  u8 *unk38;
  u8 _3C[0x30];
  u8 *unk6C;
};
struct R8ptr66
{
  u8 _0[0x2C];
  u8 _2C[0x90];
  s32 unkBC;
};
struct R466
{
  u8 _0[0x40];
  s32 unk40;
  u8 _44[0x08];
  s32 unk4C;
};
extern u8 D_02025FF0[];
extern u8 D_02021E90[];
extern u8 D_02025368[];
extern u32 D_08671BD0;
extern u32 D_08671BC0;
extern u32 D_08671BD8;
extern s32 sub_0806C4B4(void *, void *);
extern void sub_0806C5EC(void *, void *, void *, void *);
extern void sub_0806AB04(void *, void *, void *, void *);
extern void sub_0806A884(void *, void *);
extern u32 sub_08003740(void *, void *);
extern s32 sub_08065CC8(s32, s32, void *, void *);
extern void sub_080C31E8(void *, void *, s32, u32);
extern void sub_080C31E4(void *, void *, u32);
extern void sub_0806C6B0(void *, void *, void *, void *);
void sub_08066A88(struct A66 *arg0)
{
  struct R8ptr66 *r5;
  u8 *new_var6;
  struct R466 *r4;
  u8 *r8;
  int new_var7;
  long new_var8;
  s32 r6res;
  u32 t;
  u32 *new_var3;
  u8 *idx;
  u8 *p6;
  u8 *new_var2;
  u8 *p5;
  u32 *new_var4;
  struct R466 *new_var5;
  s32 rvraw;
  u16 rv;
  struct R466 *new_var;
  u32 *pd;
  u16 a;
  u16 b;
  volatile char c;
  u16 d;
  r5 = (struct R8ptr66 *) (*arg0).unk6C;
  r4 = (struct R466 *) (((u8 *) r5) + 4);
  new_var6 = D_02025368;
  r8 = arg0->unk38;
  r6res = sub_0806C4B4(r4, r4);
  if (r6res != 0)
  {
    return;
  }
  new_var2 = r8;
  new_var5 = r4;
  sub_0806C5EC(arg0, new_var2, new_var5, new_var5);
  sub_0806AB04(arg0, r8, new_var5, new_var5);
  if (new_var5->unk40 == 0)
  {
    new_var5->unk4C = 1;
    ;
    ((u8 *) (((u32) (arg0->unk22 * 2)) + ((u32) arg0)))[0x19] = 0;
    new_var4 = &D_08671BD0;
    pd = new_var4;
    sub_080C31E8(((u8 *) arg0) + 0x18, ((u8 *) arg0) + 0x22, 4, *pd);
  }
  sub_0806A884(r8, new_var5);
  t = sub_08003740(((u8 *) r5) + 0x2C, r8);
  if (t == 0)
  {
    r5->unkBC = r5->unkBC - 1;
    if (!(r5->unkBC == 0))
    {
      idx = (u8 *) (((u32) (arg0->unk22 * 2)) + ((u32) arg0));
      idx[0x19] = 0;
      ;
      new_var3 = &D_08671BC0;
      sub_080C31E4(((u8 *) arg0) + 0x18, ((u8 *) arg0) + 0x22, *new_var3);
    }
    else
    {
      idx = (u8 *) (((u32) (arg0->unk22 * 2)) + ((u32) arg0));
      idx[0x17] = 0;
      a = *((u16 *) (D_02025FF0 + 0x28));
      p5 = ((u8 *) arg0) + 0x18;
      p6 = ((u8 *) arg0) + 0x22;
      rvraw = sub_08065CC8((s32) arg0, (s32) r8, new_var5, new_var5);
      rv = (u16) rvraw;
      pd = &D_08671BD8;
      sub_080C31E8(p5, p6, rv, *pd);
    }
  }
  new_var7 = 0x3BE;
  if ((*((u32 *) (D_02025FF0 + 0x24))) != 0)
  {
    b = *((u16 *) (new_var7 + new_var6));
    if ((b & a) == 0)
    {
      do
      {
      }
      while (0);
      goto BE0;
    }
  }
  else
  {
    new_var8 = *((u16 *) (D_02021E90 + 0x146C));
    c = new_var8;
    d = *((u16 *) (D_02025368 + new_var7));
    if ((d & c) == 0)
    {
      do
      {
      }
      while (0);
      goto BE0;
    }
  }
  ;
  ((u8 *) (((u32) (arg0->unk22 * 2)) + ((u32) arg0)))[0x17] = 0;
  p5 = ((u8 *) arg0) + 0x18;
  p6 = ((u8 *) arg0) + 0x22;
  rvraw = sub_08065CC8((s32) arg0, (s32) r8, new_var5, new_var5);
  rv = (u16) rvraw;
  new_var = new_var5;
  pd = &D_08671BD8;
  sub_080C31E8(p5, p6, rv, *(&D_08671BD8));
  BE0:
  sub_0806C6B0(arg0, r8, new_var, new_var5);

  return;
}

