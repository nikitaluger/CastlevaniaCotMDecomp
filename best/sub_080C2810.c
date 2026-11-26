extern u32 sub_080C2500(void *p);
extern s64 sub_080C37B4(u32 a, u32 b, u32 c, u32 d);
extern void sub_080C25B8(s32 *a, void *b);
void sub_080C2810(s32 arg0, s32 arg1)
{
  u32 *new_var2;
  u32 sp[14];
  u32 *r7;
  u32 *ptr4;
  u32 *r8;
  void *ptr0;
  u32 r0;
  int new_var3;
  u32 new_var[2];
  u32 r2;
  u32 r4;
  s32 r5;
  s32 r6;
  sp[12] = (u32) arg0;
  sp[13] = (u32) arg1;
  sub_080C25B8((s32 *) (&sp[12]), (void *) (&sp[0]));
  sub_080C25B8((s32 *) (&sp[13]), (void *) (&sp[4]));
  r7 = &sp[0];
  ptr4 = &sp[4];
  do { do { r8 = &sp[8]; } while (0); } while (0);
  r0 = 0;
  new_var[1] = sp[0];
  new_var3 = new_var[1] <= 1;
  if (new_var3)
  {
    r0 = 1;
  }
  if (r0 != 0)
  {
    goto L_A0;
  }
  r2 = 0;
  r0 = sp[4];
  if (r0 <= 1)
  {
    r2 = 1;
  }
  if (r2 != 0)
  {
    r0 = sp[1];
    goto L_C0;
  }
  r2 = 0;
  if (new_var[1] == 4)
  {
    r2 = 1;
  }
  if (r2 == 0)
  {
    goto L_72;
  }
  new_var[1] = 0;
  if (r0 == 2)
  {
    new_var[1] = 1;
  }
  if (new_var[1] != 0)
  {
    goto L_8A;
  }
  L_72:
  r2 = 0;

  if (r0 == 4)
  {
    r2 = 1;
  }
  if (r2 == 0)
  {
    goto L_94;
  }
  r0 = 0;
  if (new_var[1] == 2)
  {
    r0 = 1;
  }
  if (r0 == 0)
  {
    goto L_BE;
  }
  goto L_8A;
  L_8A:
  ptr0 = (void *) 0x02021E68;

  goto L_END;
  L_94:
  r2 = 0;

  if (new_var[1] == 2)
  {
    r2 = 1;
  }
  if (r2 != 0)
  {
    goto L_A0;
  }
  L_B2:
  new_var[1] = 0;

  if (1 == 2)
  {
    new_var[1] = 1;
  }
  if (new_var[1] == 0)
  {
    goto L_D0;
  }
  goto L_BE;
  L_A0:
  r0 = sp[1];

  new_var[1] = sp[5];
  r0 ^= new_var[1];
  new_var[1] = (u32) (-((s32) r0));
  new_var[1] |= r0;
  new_var[1] >>= 31;
  sp[1] = new_var[1];
  ptr0 = (void *) r7;
  goto L_END;
  L_BE:
  r0 = sp[1];

  new_var2 = ptr4;
  L_C0:
  new_var[1] = sp[5];

  r0 ^= new_var[1];
  new_var[1] = (u32) (-((s32) r0));
  new_var[1] |= r0;
  new_var[1] >>= 31;
  sp[5] = new_var[1];
  ptr0 = (void *) new_var2;
  goto L_END;
  goto L_A0;
  L_D0:
  {
    unsigned long long r0c;
    u32 r2c;
    s64 res;
    r0c = r7[3];
    new_var[1] = 0;
    r2c = sp[7];
    new_var[0] = 0;
    res = sub_080C37B4(r0c, 0, r2c, 0);
    r2 = (u32) (res >> 32);
    r5 = (s32) r2;
    r6 = (s32) ((u32) res);
    r4 = r7[2];
    r0 = sp[6];
    r4 = r4 + r0;
    sp[10] = r4;
    new_var[1] = r7[1];
    r0 = sp[5];
    new_var[1] ^= r0;
    r0 = (u32) (-((s32) new_var[1]));
    r0 |= new_var[1];
    r0 >>= 31;
    sp[9] = r0;
    r4 += 2;
    sp[10] = r4;
    if (r5 < 0)
    {
      u32 mask;
      u32 bit;
      mask = 1;
      bit = 0x80000000;
      do
      {
        r4 += 1;
        do
        {
          r0 = ((u32) r5) & mask;
        }
        while (0);
        if (r0 != 0)
        {
          r6 = (s32) (((u32) r6) >> 1);
          r6 |= (s32) bit;
        }
        r5 = (s32) (((u32) r5) >> 1);
      }
      while (r5 < 0);
      sp[10] = r4;
    }
    r0 = 0x3FFFFFFF;
    if (((u32) r5) > ((u32) r0))
    {
      goto L_42;
    }
    {
      u32 r4m;
      u32 r3m;
      r4m = 0x80000000;
      r3m = 1;
      r2 = r0;
      new_var[1] = sp[10];
      do
      {
        do
        {
          new_var[1] -= 1;
          r5 = r5 << 1;
          r0 = ((u32) r6) & r4m;
          if (r0 != 0)
          {
            r5 |= r3m;
          }
          r6 = r6 << 1;
        }
        while (((u32) r5) <= ((u32) r2));
        sp[10] = new_var[1];
      }
      while (0);
    }
    L_42:
    r0 = ((u32) r5) & 0x7F;

    if (r0 != 0x40)
    {
      goto L_58;
    }
    r0 = ((u32) r5) & 0x80;
    if (r0 != 0)
    {
      goto L_56;
    }
    if (0 == r6)
    {
      goto L_58;
    }
    L_56:
    r5 += 0x40;

    L_58:
    sp[11] = (u32) r5;

    r0 = 3;
    do { do { do { r8[0] = r0; } while (0); } while (0); } while (0);
    ptr0 = (void *) r8;
    goto L_END;
  }

  L_END:
  sub_080C2500(ptr0);

}
