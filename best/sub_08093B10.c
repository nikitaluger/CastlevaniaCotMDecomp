void playSound(s32);
void sub_080C31E4(void *, void *, s32);
extern u8 D_08100818[];
extern u8 D_081007D0[];
void sub_08093E1C(void *arg0);
void sub_08093658(void *arg0);
s32 sub_08093B10(void)
{
  int new_var;
  s16 *p = (s16 *) 0x020279E8;
  s16 v = p[0];
  if (v > 5)
  {
    return -1;
  }
  new_var = 4;
  if (v < new_var)
  {
    return -1;
  }
  return 0;
}

