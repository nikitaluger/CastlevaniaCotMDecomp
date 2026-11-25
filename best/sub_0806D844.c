extern u8 D_02025368[];
void sub_0806D860(s16 arg0);
void sub_0806D844(s32 arg0)
{
  u8 *b = D_02025368;
  s32 *p = (s32 *) (b + 0x2CC);
  s32 new_var;
  new_var = (*p = arg0);
  if ((*p) < 0)
  {
    *p = 0;
  }
}

