extern u8 gGameStatus[];
void sub_0806D860(s16 arg0);
void sub_0806D844(s32 arg0)
{
  u8 *b;
  s32 *p;
  s32 *p_b1;
  s32 new_var;
  do { b = gGameStatus; } while (0);
  p = (s32 *) (b + 0x2CC);
  new_var = (*p = arg0);
  if ((*p) < 0)
  {
    *p_b1 = 0;
  }
}

