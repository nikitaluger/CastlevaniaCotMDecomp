extern void *D_0201E8A0;
extern u8 D_0201E3A0[];
void sub_080008A0(void *, s32);
void *allocMotionTracker(void)
{
  u8 *slot = D_0201E3A0;
  void *cur;
  s32 i = 0;
  void *last;
  u32 zero;
  u32 new_var2;
  u32 *new_var3;
  for (;;)
  {
    if (!((*slot) & 0x80))
    {
      cur = D_0201E8A0;
      last = NULL;
      zero = 0;
      new_var2 = 0;
      loop:
      if (cur == NULL)
      {
        goto doneloop;
      }
      last = cur;
      cur = *((void **) (((u8 *) last) + 0x10));
      goto loop;
      doneloop:
      if (last == NULL)
      {
        if (1)
        {
          D_0201E8A0 = slot;
        }
      }
      else
      {
        *((void **) (((u8 *) last) + 0x10)) = slot;
      }
      sub_080008A0(slot, 0x14);
      *slot = (*slot) | 0x80;
      new_var3 = (u32 *) (slot + 0x10);
      *new_var3 = zero;
      return (u8 *)(slot + new_var2);
    }
    i++;
    slot += 0x14;
    if (i > 0x3F)
    {
      return NULL;
    }
  }
}
