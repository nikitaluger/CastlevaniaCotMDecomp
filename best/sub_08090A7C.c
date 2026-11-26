volatile char sub_08090A7C(void)
{
  s16 temp_r0;
  temp_r0 = *((s16 *) 0x020279E8);
  switch (temp_r0)
  {
    case 0:
      return 0;

    case 2:
      return 1;

    default:
      return -1;

  }

}

