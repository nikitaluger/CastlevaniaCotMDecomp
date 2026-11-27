s32 sub_08094374(void)
{
  s16 value = *(s16 *)0x020279E8;
  if (value == 0x0D)
  {
    return 0;
  }
  return -1;
}

s32 getSpawnBehaviorIndex(void) {
    if (*(s16 *)0x020279E8 == 6) {
        return 0;
    }
    return -1;
}

s32 sub_08096F5C(void) {
    if (*(s16 *)0x020279E8 == 0xB) {
        return 0;
    }
    return 1;
}

s32 sub_08097234(void)
{
  if (*(s16 *)0x020279E8 == 0x10)
  {
    return 0;
  }
  return -1;
}
