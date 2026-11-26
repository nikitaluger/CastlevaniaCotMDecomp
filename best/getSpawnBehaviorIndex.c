volatile unsigned char getSpawnBehaviorIndex(void)
{
  if ((*((s16 *) 0x020279E8)) == 6)
  {
    return 0;
  }
  return -1;
}

