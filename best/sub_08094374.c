volatile unsigned char sub_08094374(void)
{
  s16 value = *((s16 *) 0x020279E8);
  if (value == 0x0D)
  {
    return 0;
  }
  return -1;
}

