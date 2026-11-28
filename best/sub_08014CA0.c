extern s32 _call_via_r1(s32, s32);
extern u64 sub_080C37B4(s32, s32, s32, s32);
extern u64 D_080C3218(s32, s32, s32, s32);
extern s32 fixedPointDistance(s32, s32);
extern s32 gTrigFuncTable;
inline s32 inline_fn(u64 arg0)
{
  return (s32) arg0;
}

inline s32 inline_fn2(s32 arg0)
{
  return arg0 >> 31;
}

s32 sub_08014CA0(volatile unsigned int arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, volatile unsigned int arg6, s32 arg7)
{
  s32 new_var;
  s32 sp0;
  s32 sp4;
  int new_var6;
  s32 sp8;
  s32 half;
  s32 base;
  s32 mask;
  s32 t0;
  int new_var7;
  s32 val2;
  s32 t2;
  int new_var4;
  s32 t3;
  u32 a0;
  u32 a1;
  u64 p;
  u64 p2;
  u64 p3;
  s32 hi2;
  s32 lo2;
  s32 hi3;
  int new_var5;
  int new_var3;
  s32 lo3;
  s32 val1;
  int new_var2;
  ;
  ;
  half = arg3 / 2;
  if (arg7 < (0x7FFF + 1))
  {
    new_var2 = (arg4 + 0x4000); base = half + new_var2;
  }
  else
  {
    new_var3 = 0x4000;
    if (hi2)
    {
      do
      {
        base = half + new_var3;
      }
      while (0);
      base = arg4 - base;
    }
    else
    {
      base = half + new_var3;
      base = arg4 - base;
    }
  }
  new_var2 = 0xFFFF;
  new_var5 = base & new_var2;
  mask = new_var5;
  do { t0 = _call_via_r1(half, gTrigFuncTable); } while (0);
  new_var7 = (((u32) arg2) >> 17) | (inline_fn2(arg2) << 15);
  a0 = arg2 << 15;
  a1 = new_var7;
  do { p = D_080C3218(a0, a1, t0, inline_fn2(t0)); } while (0);
  sp8 = inline_fn((u32) p);
  t2 = _call_via_r1(0x4000 + mask, gTrigFuncTable);
  p2 = sub_080C37B4(t2, inline_fn2(t2), sp8, (sp8 >> 26) >> 5);
  ;
  lo2 = inline_fn(p2);
  new_var4 = inline_fn2(sp8);
  if (((s32) (p2 >> 32)) < 0)
  {
    u64 t;
    t = p2 + 0xFFFF;
    hi2 = inline_fn(t >> 32);
    lo2 = inline_fn(t);
  }
  lo2 = hi2 << 16;
  val1 = lo2 | (((u32) lo2) >> 16);
  new_var = gTrigFuncTable;
  t3 = _call_via_r1(mask, new_var);
  p3 = sub_080C37B4(t3, inline_fn2(t3), sp8, new_var4);
  ;
  mask = (lo3 = (s32) p3);
  if (((s32) (p3 >> 32)) < 0)
  {
    u64 t;
    t = p3 + 0xFFFF;
    hi3 = inline_fn(t >> 32);
    lo3 = (s32) t;
  }
  val2 = 16;
  sp4 = lo3;
  do { t0 = (hi3 << val2); } while (0); val2 = t0 | (((u32) sp4) >> 16);
  new_var6 = arg6 - ((char) (arg1 + val2));
  if (fixedPointDistance(arg5 - (arg0 + val1), new_var6) < sp8)
  {
    if (lo2)
    {
      return 0;
    }
    else
    {
      return 0;
    }
  }
  return 1;
}
