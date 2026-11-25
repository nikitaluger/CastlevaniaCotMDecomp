extern void *sub_0805FAEC(void *, s32);
extern void *D_02025FF0;
void sub_080B73AC(void *a, s32 b)
{
  void *src;
  void *dst;
  u32 flag;
  s32 v;
  void **new_var;
  new_var = (void **) (((u8 *) D_02025FF0) + 0x1870);
  src = *((void **) (((u8 *) a) + 0x3C));
  dst = sub_0805FAEC(*new_var, 0xE4 << 1);
  if (dst != 0)
  {
    unsigned long long tmp;
    s32 nv;
    *((u32 *) (((u8 *) dst) + 0x4C)) = *((u32 *) (((u8 *) src) + 8));
    nv = (tmp = *((u32 *) (((u8 *) src) + 0xC)));
    *((u32 *) (((u8 *) dst) + 0x5C)) = nv + 0xFFEA0000;
    flag = (*((u16 *) (((u8 *) (*((void **) (((u8 *) a) + 0x38)))) + 2))) & 0x10;
    v = -1;
    if (flag)
    {
      v = 1;
    }
    *((s8 *) (((u8 *) dst) + 0x6C)) = v;
    *((s8 *) (((u8 *) dst) + 0x70)) = b;
  }
}

