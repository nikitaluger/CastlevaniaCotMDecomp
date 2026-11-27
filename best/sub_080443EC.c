extern s32 sub_08014090(s32);
extern void *spawnBudgetedEffect(void *, s32);
extern unsigned int scaleByRandom(u32);
struct D25FF0_443EC
{
  u8 _p[0x18A8];
  u8 idx;
};
struct D21E90_443EC
{
  u8 _p[0x1278];
  u32 vals[1];
};
extern struct D25FF0_443EC gMainWorkspace;
extern struct D21E90_443EC gCameraState;
void sub_080443EC(void *arg0)
{
  s32 r4 = 0;
  s32 b;
  void *r5;
  u8 *p;
  s32 v;
  u8 idx;
  s32 new_var2;
  u8 *new_var;
  u32 off;
  u8 *q;
  u32 tmp;
  s32 lo;
  s32 hi;
  s32 a;
  s32 base;
  s32 upper;
  if (sub_08014090(0x33) != 0)
  {
    return;
  }
  new_var = ((u8 *) arg0) + 0x30;
  r5 = *((void **) new_var);
  while (r5 != 0)
  {
    r4++;
    r5 = *((void **) (((u8 *) r5) + 0x2C));
  }

  if (r4 > 7)
  {
    return;
  }
  p = ((u8 *) arg0) + 0x7C;
  v = ((s32) (*p)) - 1;
  *p = (u8) v;
  if (((s8) v) != 0)
  {
    return;
  }
  *p = 0x2D;
  r5 = spawnBudgetedEffect(arg0, 0x8D << 1);
  if (r5 == 0)
  {
    return;
  }
  {
    u8 *p1 = (u8 *) (&gCameraState);
    idx = gMainWorkspace.idx;
    off = (idx + 1) << 6;
    q = p1 + 0x1278;
    tmp = *((u32 *) (off + q));
    lo = ((s32) tmp) + 0x8000;
    hi = ((s32) tmp) + 0xF08000;
    upper = b;
    a = (base = *((s32 *) (((u8 *) arg0) + 0x5C)));
    upper = (b = *((s32 *) (((u8 *) arg0) + 0x6C)));
    new_var2 = a;
    if ((lo < new_var2) && (hi > b))
    {
      goto compute;
    }
    if ((hi < new_var2) || (lo > b))
    {
      goto compute;
    }
    if (lo < new_var2)
    {
      base = a;
      upper = (new_var2 = hi);
    }
    else
      if ((((s32) tmp) + 0xF08000) <= b)
    {
      base = lo;
      upper = new_var2;
    }
    else
    {
      base = lo;
    }
    compute:
    *((u32 *) (((u8 *) r5) + 0x4C)) = (u32) (scaleByRandom((u32) (upper - base)) + base);

    *((u32 *) (0x5C + ((u8 *) r5))) = *((u32 *) (((u8 *) arg0) + 0x3C));
    *((u32 *) (((u8 *) r5) + 0x6C)) = *((u32 *) (((u8 *) arg0) + 0x4C));
  }
}

