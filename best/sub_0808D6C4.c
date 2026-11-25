extern u8 D_02021E90[];
inline u8 *inline_fn(s32 arg0)
{
  return ((u8 *) arg0) + 0x39;
}

void sub_0808D6C4(s32 a, s32 b)
{
  u8 *p = ((u8 *) b) + 0x3B;
  u8 *p3d = (p + 2) + a;
  u8 *p3b = p + a;
  u8 sum = (*p3d) + (*p3b);
  u8 *p39 = inline_fn(b) + a;
  s32 idx;
  u8 *new_var;
  p++;
  p--;
  if ((*p39) >= sum)
  {
 do { } while (0);
    *p39 = 0;
  }
  if ((*p39) < (*p3b))
  {
    D_02021E90[0x1460 + a] = *((volatile s16 *) ((((u8 *) b) + (a * 4)) + 6));
    new_var = (u8 *) b;
    D_02021E90[0x1464 + a] = *((volatile s16 *) ((new_var + (a * 4)) + 0x16));
    D_02021E90[0x1462 + a] = *((volatile s16 *) ((((u8 *) b) + (a * 4)) + 0x0E));
    D_02021E90[0x1466 + a] = *((volatile s16 *) ((new_var + (a * 4)) + 0x1E));
    D_02021E90[0x1468 + a] = 0x31;
  }
  else
  {
    D_02021E90[0x1460 + a] = *((volatile s16 *) ((((u8 *) b) - (-(a * 4))) + 6));
    {
      D_02021E90[0x1462 + a] = *((volatile s16 *) ((((u8 *) b) + (a * 4)) + 0x0E));
      D_02021E90[0x1464 + a] = *((volatile s16 *) ((new_var + (a * 4)) + 0x16));
      D_02021E90[0x1466 + a] = *((volatile s16 *) ((new_var + (a * 4)) + 0x1E));
    }
    D_02021E90[0x1468 + a] = *((u8 *) (new_var + 0x38));
  }
}
