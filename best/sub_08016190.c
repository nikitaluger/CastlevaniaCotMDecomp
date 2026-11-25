extern void *D_020202A8;
extern u8 D_0201E8A8[];
void sub_080008A0(void *, s32);
void *sub_08016190(void)
{
  u8 *slot = D_0201E8A8;
  void *cur;
  s32 i = 0;
  void *last;
  u32 zero;
  short new_var2;
  u32 *new_var3;
  for (;;)
  {
    if (!((*slot) & 0x80))
    {
      cur = D_020202A8;
      last = NULL;
      zero = 0;
      new_var2 = 0;
      loop:
      if (cur == NULL)
      {
        goto doneloop;
      }

      last = cur;
      cur = *((void **) (((u8 *) last) + 0x20));
      goto loop;
      doneloop:
      if (last == NULL)
      {
        if (1)
        {
          D_020202A8 = slot;
        }
      }
      else
      {
        *((void **) (((u8 *) last) + 0x20)) = slot;
      }

      sub_080008A0(slot, 0x34);
      *slot = (*slot) | 0x80;
      new_var3 = (u32 *) (slot + 0x20);
      *new_var3 = zero;
      return (u8 *) (slot + new_var2);
    }
    i++;
    slot += 0x34;
    if (i > 0x7F)
    {
      return NULL;
    }
  }

}

