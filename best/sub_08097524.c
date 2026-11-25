void sub_08011344(s32, s32, s16, s32);
s32 sub_080979EC(void *);
void sub_080C31E0(s32, s32);
void sub_080C31E8(void *, void *, s32, s32);
struct Arg0
{
  u8 _0[0x14];
  u32 f14;
  u8 _18[0xA];
  s16 f22;
  u8 _24[0x14];
  void *f38;
  void *f3C;
  u8 _40[0x6C];
  void *fAC;
};
struct R6Sub
{
  u8 _0;
  u8 f01;
  u8 _02[4];
  u16 f06;
};
struct R6
{
  u32 f00;
  struct R6Sub *f04;
  u8 _08[8];
  s32 f10;
  u16 f14;
  u8 _16[2];
  u16 f18;
};
struct R4
{
  u8 _0[4];
  struct R6Sub *f04;
};
extern u8 D_08100B98[];
void sub_08097524(u8 *arg0)
{
  s32 r9;
  void *r8;
  struct R4 *r4;
  struct R6 *r6;
  struct R6 *r7;
  s32 i;
  u8 *b;
  u8 *p18;
  u32 *gp;
  s32 funcptr;
  u8 zero;
  r8 = *((void **) (arg0 + 0x38));
  r4 = *((struct R4 **) (arg0 + 0xAC));
  r6 = *((struct R6 **) (arg0 + 0x3C));
  r7 = (struct R6 *) (((u8 *) r6) + 0x1C);
  r9 = sub_080979EC(arg0);
  if (r9 == 1)
  {
    u8 *tbl = D_08100B98;
    sub_08011344((s32) r8, (s32) r7, *((s16 *) (tbl + (r6->f00 << 2))), 0);
    r6->f04->f01 = 0;
    zero = 0;
    r6->f14 = r9;
    goto common;
  }
  if (r4->f04->f06 & 1)
  {
    u8 *tbl = D_08100B98;
    sub_08011344((s32) r8, (s32) r7, *((s16 *) (tbl + (r6->f00 << 2))), 0);
    r6->f04->f01 = 0;
    zero = 0;
    r6->f14 = 1;
    r6->f18 = 1;
    common:
    *((u8 *) ((((u32) (*((s16 *) (arg0 + 0x22)))) * 2) + ((u32) arg0) + 0x19)) = zero;
    gp = (u32 *) 0x08671BD0;
    p18 = arg0 + 0x18;
    sub_080C31E8(p18, arg0 + 0x22, 3, *gp);
    b = (u8 *) ((((u32) (*((s16 *) (arg0 + 0x22)))) * 2) + ((u32) arg0));
    *((u8 *) (b + 0x19)) = (*((u8 *) (b + 0x19))) + 1;
    i = 2;
    i = ((s32) ((s16) (*((s16 *) (arg0 + 0x22))))) * i;
    p18 += i;
    funcptr = *((s32 *) (((u32) ((*((u8 *) p18)) * 4)) + (*((u32 *) (arg0 + 0x14)))));
    sub_080C31E0((s32) arg0, funcptr);
    return;
  }
  {
    struct R6Sub *sub = r6->f04;
    s32 v = r6->f10;
    if (v < 0)
    {
      v += 0xFFFF;
    }
    sub->f06 = (v >> 16) - 0x1F;
  }
  {
    u8 *tbl = D_08100B98;
    u8 *tbl2 = tbl + 2;
    sub_08011344((s32) r8, (s32) r7, *((s16 *) (tbl2 + (r6->f00 << 2))), 0);
  }
  zero = 0;
  *((u8 *) ((((u32) (*((s16 *) (arg0 + 0x22)))) * 2) + ((u32) arg0) + 0x19)) = zero;
  gp = (u32 *) 0x08671BD0;
  p18 = arg0 + 0x18;
  sub_080C31E8(p18, arg0 + 0x22, 1, *gp);
  ;
  *((u8 *) (((u8 *) ((((u32) (*((s16 *) (arg0 + 0x22)))) * 2) + ((u32) arg0))) + 0x19)) = (*((u8 *) (((u8 *) ((((u32) (*((s16 *) (arg0 + 0x22)))) * 2) + ((u32) arg0))) + 0x19))) + 1;
  i = ((s32) ((s16) (*((s16 *) (arg0 + 0x22))))) * 2;
  p18 += i;
  funcptr = *((s32 *) (((u32) ((*((u8 *) p18)) * 4)) + (*((u32 *) (arg0 + 0x14)))));
  sub_080C31E0((s32) arg0, funcptr);
}
