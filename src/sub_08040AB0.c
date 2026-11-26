extern void *sub_0805FAEC(void *, s32);
struct S4
{
  s32 a;
  s32 b;
  s32 c;
  s32 d;
};
extern struct S4 D_080CF490;
void sub_08040AB0(u8 *arg0, u8 *arg1, u8 *arg2)
{
  s32 v;
  void *a1;
  s32 s[4];
  s32 baseval;
  s32 tmp;
  void *ret;
  u8 *new_var;
  s32 *new_var2;
  u8 *p4;
  v = -1;
  a1 = arg1;
  *(struct S4 *)s = D_080CF490;
  tmp = *((u8 *) ((arg0 + (((s32) (*((s16 *) (arg0 + 0x22)))) * 2)) + 0x19));
  if (tmp == 0x28)
  {
    v = 0;
  }
  if (tmp == 0x50)
  {
    v = 1;
  }
  if (v >= 0)
  {
    new_var2 = &tmp;
    ret = sub_0805FAEC(arg0, 0x106);
    if (ret != 0)
    {
      tmp = s[v * 2];
      baseval = *((s32 *) (arg2 + 8));
      if (!((*((u16 *) (((u8 *) a1) + 2))) & 0x10))
      {
        *((s32 *) (ret + 0x4C)) = baseval - tmp;
      }
      else
      {
        *((s32 *) (ret + 0x4C)) = (baseval) + ((*new_var2));
      }
      p4 = ((u8 *) s) + 4;
      baseval = (v * 8); new_var = p4 + baseval;
      *((s32 *) (ret + 0x5C)) = (*((s32 *) (arg2 + 0xC))) + (*((s32 *) new_var));
    }
  }
}
