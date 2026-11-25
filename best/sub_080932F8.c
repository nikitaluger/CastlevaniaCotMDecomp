extern u16 D_020279E8;
s32 sub_080932F8(void)
{
  s32 v = ((s32) D_020279E8) - 3;
  v = (s32) (((u32) v) << 16);
  v = v >> 16;
  if (((u32) v) > 0x0C)
  {
    return -1;
  }
  switch (v)
  {
    case 0:
      return 0;

    case 1:

    case 2:
      return 2;
      return 1;

    case 4:

    case 6:
      return 3;

    case 12:
      return 4;

    default:
      return -1;

  }

}

