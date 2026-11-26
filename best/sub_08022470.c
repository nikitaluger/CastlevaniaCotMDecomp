extern void sub_080113A8(s32, void *);
extern void sub_0801165C(void *, s32);
extern s32 sub_08013B5C(s32);
extern s32 sub_0805F9B4(s32, s32);
extern void sub_080227D4(s32);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E8(void *, void *, s32, s32);
extern s32 sub_08005820(s32);
extern u8 gCameraState[];
extern u8 gMainWorkspace[];
struct B1
{
  u8 f0;
  u8 f1;
};
inline int inline_fn(s16 arg0, int arg1, u8 *arg2)
{
  return (((u32) arg0) * arg1) + ((u32) arg2);
}

inline u8 *inline_fn2(u8 *arg0)
{
  return *((u8 **) arg0);
}

void sub_08022470(u8 *arg0)
{
  s32 a;
  u8 *p;
  u8 *p_copy;
  u8 *r8;
  struct B1 *new_var2;
  u8 *p48;
  u8 *p28;
  u8 *q;
  s32 i;
  u8 *b;
  u8 bb;
  void **tbl;
  void *vv;
  u8 *pt;
  u8 *pb;
  s32 *new_var3;
  u8 *base1;
  u32 idx;
  s32 *new_var;
  a = *((s32 *) (arg0 + 0x38));
  p = *((u8 **) (arg0 + 0x3C));
  r8 = p + 0x34;
  p48 = p + 0x48;
  p28 = inline_fn2(p + 0x28);
  new_var2 = (struct B1 *) p28;
  new_var2->f1 |= 1;
  p28 = *((u8 **) (p48 + 0x34));
  ((struct B1 *) p28)->f1 |= 1;
  p28 = *((u8 **) (p48 + 0x38));
  ((struct B1 *) p28)->f1 |= 1;
  new_var = (s32 *) (p + 8);
  if (((*((s16 *) p48)) == 1) && (sub_0805F9B4(*new_var, *((s32 *) (p + 0xC))) == 1))
  {
    sub_080C31E0(arg0, *((void **) (arg0 + 0x24)));
    return;
  }
  p_copy = p;
  if (((*((u16 *) (arg0 + 0x6C))) & 2) != 0)
  {
    if (pb || p_copy)
    {
      *((u16 *) p_copy) |= 1;
    }
    else
    {
      *((u16 *) p_copy) |= 1;
    }
  }
  if (((*((u16 *) p_copy)) & 1) != 0)
  {
    p28 = *((u8 **) (p_copy + 0x28));
    ((struct B1 *) p28)->f1 = (((struct B1 *) p28)->f1 = ~1);
    p28 = *((u8 **) (p48 + 0x34));
    ((struct B1 *) p28)->f1 &= ~1;
    if ((*((u8 *) (inline_fn(*((s16 *) (arg0 + 0x22)), 2, arg0) + 0x1A))) != 2)
    {
      *((s32 *) (p48 + 4)) = 0x16C1;
      p28 = *((u8 **) (p48 + 0x38));
      *((s32 *) (p_copy + 0x10)) = 0;
      *((s32 *) (p_copy + 0x14)) = sub_08005820(0x10001) + 0x8000;
      *((u8 *) (inline_fn(*((s16 *) (arg0 + 0x22)), 2, arg0) + 0x1B)) = 0;
      new_var3 = &(*((s32 *) 0x08671BDC));
      sub_080C31E8(arg0 + 0x18, arg0 + 0x22, 2, *new_var3);
    }
  }
  if (sub_08013B5C(a) == 0)
  {
    *((void **) (arg0 + 0x14)) = (void *) 0x0866D878;
    *((u16 *) (arg0 + 0x22)) = (u16) ((*((u16 *) (arg0 + 0x22))) + 1);
    q = (u8 *) inline_fn(*((s16 *) (arg0 + 0x22)), 2, arg0);
    *((u8 *) (q + 0x19)) = (u8) ((*((u8 *) (q + 0x19))) + 1);
    i = 2;
    i = (*((s16 *) (arg0 + 0x22))) * i;
    b = arg0 + 0x18;
    pb = b;
    bb = *(pb + i);
    tbl = *((void ***) (arg0 + 0x14));
    base1 = arg0;
    vv = tbl[bb];
    sub_080C31E0(base1, vv);
    *((u16 *) (base1 + 0x22)) = (u16) ((*((u16 *) (base1 + 0x22))) - 1);
    if (((*((u16 *) (arg0 + 2))) & 0x8000) == 0)
    {
      if ((*((u16 *) p_copy)) == 0)
      {
        sub_080113A8(a, r8);
      }
      sub_0801165C(p_copy, *((s32 *) (p48 + 4)));
    }
  }
  else
  {
    u8 *base2;
    sub_080227D4(a);
    pt = gCameraState;
    q = gMainWorkspace;
    pb = q;
    pb += 0x18A8;
    idx = (((u32) (*pb)) + 1) * 0x40;
    base1 = pt + 0x1278;
    *((u32 *) (((u8 *) a) + 0x14)) = (*((u32 *) (((u8 *) p_copy) + 0x08))) - (((*((u32 *) (base1 + idx))) + 0x8000) & 0xFFFF0000);
    idx = (((u32) (*pb)) + 1) * 0x40;
    base2 = pt + 0x127C;
    do { *((u32 *) (((u8 *) a) + 0x18)) = (*((u32 *) (b = ((u8 *) p_copy) + 0x0C))) - (((*((u32 *) (base2 + idx))) + 0xFFFF8000) & 0xFFFF0000); } while (0);
  }
}

