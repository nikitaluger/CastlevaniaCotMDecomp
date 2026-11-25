extern u32 D_02020BC4;
s32 sub_080168F8(void)
{
  void *p = (void *) D_02020BC4;
  s32 result;
 do { if (p != NULL) { p = ((u8 *) p) + 4; D_02020BC4 = (u32) (*((void **) p)); result = *((s32 *) p); } else { result = 0; } } while (0);
  return result;
}
