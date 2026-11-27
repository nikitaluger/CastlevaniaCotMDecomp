s32 sub_08014990(s32);
void *hitTestEntities(s32);
void sub_0808E9AC(s32, s32, s32);
extern u8 gCameraState[];
extern u8 gMainWorkspace[];
inline u8 *inline_fn(void *arg0)
{
  return (u8 *) arg0;
}

s32 sub_080457E0(void *arg0)
{
  void *p38;
  void *p3C;
  u8 *r6;
  s32 *new_var4;
  s32 result;
  void *r4;
  s32 cur;
  s16 new_var6;
  s32 off;
  s32 addr;
  s32 val;
  u8 *base;
  s32 lim;
  u8 *t;
  u8 *new_var3;
  s32 *new_var5;
  u16 f6;
  u8 *new_var2;
  s32 *new_var;
  u32 k;
  t = *((void **) (((u8 *) arg0) + 0x3C));
  p38 = *((void **) (((u8 *) arg0) + 0x38));
  p3C = t;
  r6 = ((u8 *) p3C) + 0x48;
  do { f6 = *((u16 *) (r6 + 6)); } while (0);
  new_var4 = (s32 *) (r6 + 0x0C);
  if (((s32) (*((s16 *) (r6 + 6)))) > 0)
  {
    result = f6 - 1;
  }
  else
  {
    if ((*new_var4) == 0)
    {
      return 0;
    }
    if (((s32) (*((s16 *) (((u8 *) p3C) + 0x20)))) > 0)
    {
      return 0;
    }
    r4 = hitTestEntities(*new_var4);
    do { if (r4 == 0)
    {
      return 0;
    } } while (0);
    new_var3 = ((u8 *) p3C) + 8;
    if (sub_08014990((s32) p38) < 0)
    {
      base = gMainWorkspace;
      new_var2 = base + 0x174C;
      cur = *((s32 *) new_var3);
      if ((*((s32 *) new_var2)) > (cur + ((s32) 0xFFF80000)))
      {
        return 0;
      }
      off = (s32) 0xFFF60000;
    }
    else
    {
      base = gMainWorkspace;
      new_var5 = (s32 *) (base + 0x174C);
      cur = *((s32 *) new_var3);
      if ((*((s32 *) new_var5)) < (cur + 0x80000))
      {
        return 0;
      }
      off = 0xA0000;
    }
    new_var6 = *((s16 *) (inline_fn(r4) + 0x32));
    addr = cur + off;
    cur = (((s32) new_var6) << 16); val = cur + ((s32) 0xFFFF8000);
    t = gCameraState;
    k = *inline_fn(base + 0x18A8);
    k = k + 1;
    k = k << 6;
    t = t + 0x127C;
    val += *((s32 *) (t + k));
    new_var = (s32 *) (inline_fn(p3C) + 0xC);
    lim = (*new_var) + ((s32) 0xFFE80000);
    if (val < lim)
    {
      val = lim;
    }
    else
      if (val > ((*new_var) + ((s32) 0xFFF80000)))
    {
      val = (*new_var) + ((s32) 0xFFF80000);
    }
    sub_0808E9AC(addr, val, 8);
    result = 6;
  }
  *((u16 *) (r6 + 6)) = result;
  return 1;
}

