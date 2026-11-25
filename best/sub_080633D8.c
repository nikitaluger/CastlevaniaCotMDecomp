extern s32 sub_0806C4B4(void *, void *);
extern void sub_0806C5EC(void *, void *, void *, void *);
extern void sub_080850B4(void *, void *);
extern s32 sub_0806B3E8(void *, void *, void *, void *);
extern s32 sub_0806B820(void *, void *, void *, void *);
extern s32 sub_0806BA98(void *, void *, void *, void *);
extern s32 sub_0806B104(void *, void *, void *);
extern void sub_0806C49C(void *, void *);
extern void sub_080C31E8(void *, void *, s32, u32);
extern void sub_0806B280(void *, void *, void *, void *);
extern void sub_0806AB04(void *, void *, void *, void *);
extern void sub_0806A7AC(void *, void *, s32);
extern void sub_0806A884(void *, void *);
extern u16 sub_0806BCD8(void *, void *, void *, void *);
extern void sub_08003740(void *, void *);
extern void sub_0806C6B0(void *, void *, void *, void *);
extern u8 D_02025368[];
extern u32 D_08671BD0;
struct Arg0
{
  u8 f00[0x18];
  u8 f18;
  u8 f19[3];
  u8 f1C[0x22 - 0x1C];
  s16 f22;
  u8 f24[0x38 - 0x24];
  void *f38;
  u8 f3C[0x6C - 0x3C];
  void *f6C;
};
struct B
{
  u8 _0[0x40];
  u32 f40;
  u8 _44[0x4C - 0x44];
  u32 f4C;
  u8 _50[0x68 - 0x50];
  u32 f68;
  u8 _6C[0xC4 - 0x6C];
  u32 fC4;
  u8 _C8[4];
  u16 fCC;
  u16 fCE;
};
struct S25FF0
{
  u8 _0[0x14ED];
  u8 f14ED;
};
extern struct S25FF0 D_02025FF0;
typedef struct 
{
  u8 pad[0x19];
  u8 field;
} Q19;
void sub_080633D8(struct Arg0 *arg0)
{
  void *p6C = arg0->f6C;
  struct B *b = (struct B *) (((u8 *) p6C) + 4);
  void *f38 = arg0->f38;
  void *p = (void *) b;
  void *glob = D_02025368;
  s32 r7;
  u16 v;
  s32 *new_var;
  u32 v32;
  u32 f4cv;
  u32 *lit0;
  u32 *lit1;
  u32 *lit2;
  u32 *lit3;
  if (sub_0806C4B4(p, p) != 0)
  {
    return;
  }
  sub_0806C5EC(arg0, f38, p, p);
  sub_080850B4(arg0, p);
  if (((sub_0806B3E8(arg0, f38, p, p) == 0) && (sub_0806B820(arg0, f38, p, p) == 0)) && (sub_0806BA98(arg0, f38, p, p) == 0))
  {
    r7 = sub_0806B104(f38, p, p);
    if (r7 == 0)
    {
      sub_0806C49C(f38, p);
      ((Q19 *) (((u8 *) arg0) + (2 * arg0->f22)))->field = r7;
      lit0 = &D_08671BD0;
      sub_080C31E8(((u8 *) arg0) + 0x18, ((u8 *) arg0) + 0x22, 4, *lit0);
    }
    else
    {
      v = b->fCC | 0xC;
      b->fCC = v;
      r7 = 0;
      if ((*((u8 *) (((u8 *) glob) + 0x3CB))) != 0)
      {
        b->fCC = v | 1;
      }
      if (b->f68 == 0)
      {
        sub_0806B280(arg0, f38, p, p);
        new_var = &r7;
        ((Q19 *) (((u8 *) arg0) + (2 * arg0->f22)))->field = *new_var;
        lit1 = &D_08671BD0;
        sub_080C31E8(((u8 *) arg0) + 0x18, ((u8 *) arg0) + 0x22, 7, *lit1);
      }
    }
  }
  sub_0806AB04(arg0, f38, b, p);
  if (arg0->f18 == 6)
  {
    if (((b->fCE & 0x100) != 0) && (b->f68 == 1))
    {
      b->f68 = 2;
      sub_0806A7AC(f38, b, 0x1E);
    }
    if (((arg0->f18 == 6) && ((b->fCE & 0x100) == 0)) && (b->f68 == 2))
    {
      b->f68 = 1;
      if (D_02025FF0.f14ED != 0x35)
      {
        sub_0806A7AC(f38, b, 7);
      }
      else
      {
        sub_0806A7AC(f38, b, 0x55);
      }
    }
  }
  if (b->f40 == 0)
  {
    f4cv = b->f4C;
    if (f4cv == 0)
    {
      sub_0806A7AC(f38, b, 0x10);
      ((Q19 *) (((u8 *) arg0) + (2 * arg0->f22)))->field = f4cv;
      lit2 = &D_08671BD0;
      sub_080C31E8(((u8 *) arg0) + 0x18, ((u8 *) arg0) + 0x22, 3, *lit2);
    }
  }
  sub_0806A884(f38, p);
  v32 = (u16) sub_0806BCD8(arg0, f38, b, p);
  b->fC4 = (u16) v32;
  if (((u16) v32) != 0)
  {
    ((Q19 *) (((u8 *) arg0) + (2 * arg0->f22)))->field = 0;
    lit3 = &D_08671BD0;
    sub_080C31E8(((u8 *) arg0) + 0x18, ((u8 *) arg0) + 0x22, b->fC4, *lit3);
  }
  sub_08003740(((u8 *) b) + 0x28, f38);
  sub_0806C6B0(arg0, f38, b, p);
}

