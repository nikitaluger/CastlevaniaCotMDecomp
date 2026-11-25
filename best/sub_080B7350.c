extern void *sub_0805FAEC(void *, s32);
struct S_02025FF0
{
  u8 _0x000[0x1870];
  u32 v;
};
extern struct S_02025FF0 D_02025FF0;
void sub_080B7350(void *arg0, s32 arg1)
{
  void *temp_r4;
  unsigned long long new_var2;
  void *temp_r0;
  u32 new_var;
  s32 var_r1;
  temp_r4 = *((void **) (((u8 *) arg0) + 0x3C));
  temp_r0 = sub_0805FAEC((void *) D_02025FF0.v, 0x1C7);
  if (temp_r0 != NULL)
  {
    *((u32 *) (((u8 *) temp_r0) + 0x4C)) = (unsigned long) (*((u32 *) (((u8 *) temp_r4) + 8)));
    new_var = (new_var2 = *((u32 *) (((u8 *) temp_r4) + 0xC)));
    *((u32 *) (((u8 *) temp_r0) + 0x5C)) = new_var + 0xFFEA0000;
    if ((*((u16 *) (((u8 *) (*((void **) (((u8 *) arg0) + 0x38)))) + 2))) & 0x10)
    {
      var_r1 = 1;
    }
    else
    {
      var_r1 = -1;
    }
    *((s8 *) (((u8 *) temp_r0) + 0x6C)) = (s8) var_r1;
    *((s8 *) (((u8 *) temp_r0) + 0x70)) = (s8) arg1;
  }
}

