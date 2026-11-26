s32 sub_0808F61C(void)
{
  volatile unsigned long long pad;
  s16 temp_r0;
  temp_r0 = *((s16 *) 0x020279E8);
  switch (temp_r0)
  {
    case 0:
      return 0;

    case 6:
      return 1;

    case 9:
      return 2;

    default:
      return -1;

  }

}

