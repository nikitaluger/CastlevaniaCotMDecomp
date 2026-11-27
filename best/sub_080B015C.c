extern void allocWorkSlot(void *, s32, s32, s32);
extern void *spawnBudgetedEffect(s32, s32);
extern void sub_080C31E0(void *, s32);
extern s32 gActiveObjectId;
inline u8 inline_fn(u32 arg0)
{
  return (u8) arg0;
}

void sub_080B015C(u8 *arg0)
{
  u8 *p;
  allocWorkSlot(arg0, 0, 0x54, 0);
  p = *((u8 **) (arg0 + 0x3C));
  if (p == 0)
  {
    sub_080C31E0(arg0, *((s32 *) (arg0 + 0x24)));
    return;
  }
  else
  {
    u8 *base7 = p + 0x48;
    u32 i = 1;
    u32 one = 1;
    u8 *p50 = arg0 + 0x50;
    s32 *p8C = (s32 *) (arg0 + 0x8C);
    s32 *pd = &gActiveObjectId;
    void **arr = (void **) base7;
    for (; i <= 3; i++)
    {
      void *t = spawnBudgetedEffect(*pd, 0x1B1);
      *arr = t;
      *((u8 *) (((u8 *) t) + 0x4C)) = one;
      *((u8 *) (((u8 *) (*arr)) + 0x50)) = inline_fn(i);
      {
        void *t2 = *(arr++);
        u8 val = *p50;
        *((u8 *) (((u8 *) t2) + 0x5C)) = val;
      }
    }

    *((s32 *) (arg0 + 0x6C)) = *((s32 *) base7);
    *((s32 *) (arg0 + 0x7C)) = *((s32 *) (base7 + 4));
    *p8C = *((s32 *) (base7 + 8));
    {
      u16 w = *((u16 *) (arg0 + 2));
      w |= 0x1000;
      w |= 0x0800;
      *((u16 *) (arg0 + 2)) = w;
    }
    {
      s32 handler = 0x080B020D;
      *((s32 *) (arg0 + 0x14)) = handler;
      *((u16 *) (arg0 + 0x22)) = 1;
      sub_080C31E0(arg0, handler);
    }
  }
}
