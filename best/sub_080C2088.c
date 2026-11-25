s32 sub_080C2088(void *arg0, void *arg1)
{
  s32 b0;
  s32 b1;
  s32 b2;
  s32 b3;
  s32 b4;
  s32 b5;
  s32 b6;
  s32 b7;
  s32 b9;
  u32 ta;
  u32 tb;
  u32 ta2;
  s32 af4;
  s32 bf4;
  s32 af8;
  s32 bf8;
  s32 res;
  u32 afC;
  u32 bfC;
  u32 af10;
  u32 bf10;
  b0 = 0;
  ta = *((u32 *) arg0);
  if (ta <= 1U)
  {
    b0 = 1;
  }
  if (b0 != 0)
  {
    return 1;
  }
  b1 = 0;
  tb = *((u32 *) arg1);
  if (tb <= 1U)
  {
    b1 = 1;
  }
  if (b1 != 0)
  {
    return 1;
  }
  b2 = 0;
  if (ta == 4)
  {
    b2 = 1;
  }
  if (b2 != 0)
  {
    b3 = 0;
    if (tb == 4)
    {
      b3 = 1;
    }
    if (b3 != 0)
    {
      return (*((s32 *) (((u8 *) arg1) + 4))) - (*((s32 *) (((u8 *) arg0) + 4)));
    }
  }
  b4 = 0;
  ta2 = *((u32 *) arg0);
  if (ta2 == 4)
  {
    b4 = 1;
  }
  if (b4 != 0)
  {
    goto tailA;
  }
  b5 = 0;
  if (tb == 4)
  {
    b5 = 1;
  }
  if (b5 != 0)
  {
    tailB:
    res = ((*((s32 *) (((u8 *) arg1) + 4))) != 0) ? (1) : (-1);

    goto ret;
  }
  b6 = 0;
  if (ta2 == 2)
  {
    b6 = 1;
  }
  if (b6 != 0)
  {
    b7 = 0;
    if (tb == 2)
    {
      b7 = 1;
    }
    if (b7 != 0)
    {
      return 0;
    }
  }
  af10 = 0;
  if (ta2 == 2)
  {
    af10 = 1;
  }
  if (af10 != 0)
  {
    goto tailB;
  }
  b9 = 0;
  if (tb == 2)
  {
    b9 = 1;
  }
  if (b9 != 0)
  {
    tailA:
    res = ((*((s32 *) (((u8 *) arg0) + 4))) != 0) ? (-1) : (1);

    goto ret;
  }
  goto f4sec;
  ret:
  return res;

  f4sec:
  bf4 = *((s32 *) (((u8 *) arg1) + 4));

  af4 = *((s32 *) (((u8 *) arg0) + 4));
  if (af4 != bf4)
  {
    return (af4 != 0) ? (-1) : (1);
  }
  af8 = *((s32 *) (((u8 *) arg0) + 8));
  bf8 = *((s32 *) (((u8 *) arg1) + 8));
  if (af8 > bf8)
  {
    return (af4 != 0) ? (-1) : (1);
  }
  if (af8 < bf8)
  {
    return (af4 != 0) ? (1) : (-1);
  }
  af10 = *((u32 *) (((u8 *) arg0) + 0x10));
  bf10 = *((u32 *) (((u8 *) arg1) + 0x10));
  if (af10 > bf10)
  {
    return (af4 != 0) ? (-1) : (1);
  }
  if (af10 == bf10)
  {
    afC = *((u32 *) (((u8 *) arg0) + 0xC));
    bfC = *((u32 *) (((u8 *) arg1) + 0xC));
    if (afC > bfC)
    {
      return (af4 != 0) ? (-1) : (1);
    }
  }
  if (bf10 > af10)
  {
    return (af4 != 0) ? (1) : (-1);
  }
  if (bf10 == af10)
  {
    bfC = *((u32 *) (((u8 *) arg1) + 0xC));
    afC = *((u32 *) (((u8 *) arg0) + 0xC));
    if (bfC > afC)
    {
      return (af4 != 0) ? (1) : (-1);
    }
  }
  return 0;
}

