void sub_080489BC(void *arg0)
{
  void *new_var;
  void *r9;
  void *r10;
  void *r8;
  void *sp0;
  void *r7;
  s32 flag;
  s32 r4;
  s32 rr;
  s32 new_var2[2];
  s8 r6;
  s8 r2;
  u16 *tbl;
  u16 val;
  s32 i;
  r9 = arg0;
  r10 = *((void **) (((u8 *) arg0) + 0x38));
  r8 = *((void **) (((u8 *) arg0) + 0x3C));
  sp0 = ((u8 *) r8) + 0x34;
  r7 = ((u8 *) r8) + 0x48;
  sub_080148D8(r10, *((s32 *) (((u8 *) r8) + 8)));
  if (sub_08049180(r10, sp0, r8, r7) != 0)
  {
    if ((*((u8 *) (((u8 *) r9) + 0x4C))) != 0)
    {
      flag = (*((u16 *) (((u8 *) r10) + 2))) & 0x10;
      if (flag)
      {
        new_var2[0] = *((s8 *) r7);
        r6 = new_var2[0] + 1;
      }
      else
      {
        new_var2[0] = 8 - (*((s8 *) r7));
        r6 = new_var2[0] - 1;
      }
      new_var = r8;
      r4 = sub_08049200(r9, new_var, new_var2[0], 0);
      rr = sub_08049200(r9, r8, r6, 0);
      if ((r4 != 0) || (rr != 0))
      {
        *((u8 *) r7) = (*((u8 *) r7)) + 1;
      }
    }
    else
    {
      flag = (*((u16 *) (((u8 *) r10) + 2))) & 0x10;
      if (flag)
      {
        new_var2[0] = *((s8 *) r7);
      }
      else
      {
        new_var2[0] = 8 - (*((s8 *) r7));
      }
      rr = sub_08049200(r9, new_var, new_var2[0], 0);
      if (rr != 0)
      {
        *((u8 *) r7) = (*((u8 *) r7)) + 1;
      }
    }
  }
  r2 = *((s8 *) r7);
  r8 = *((void **) (((u8 *) arg0) + 0x3C));
  tbl = (u16 *) 0x080CF900;
  new_var2[1] = *((u8 *) (((u8 *) r9) + 0x4C));
  if (r2 == ((s8) val))
  {
    sub_08049160(r10, sp0, r7, 0);
    i = *((s16 *) (((u8 *) r9) + 0x22));
    ((u8 *) r9)[(i * 2) + 0x19] = 0;
    sub_080C31E4(((u8 *) r9) + 0x18, ((u8 *) r9) + 0x22, *((s32 *) 0x08671BB0));
  }
}
