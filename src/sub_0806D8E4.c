extern void sub_0806D930(void);
extern u8 D_02025368[];
inline int inline_fn(s16 arg0, s16 arg1)
{
  return arg0 + (((u32) arg1) >> 31);
}

/* Recalculates stats, then commits two saved word pairs and stores a rounded
 * half of the s16 value at +0x2D6 into +0x2D4. */
void sub_0806D8E4(void)
{
  u8 *stats = D_02025368;
  sub_0806D930();
  *((u32 *) (stats + 0x2C4)) = *((u32 *) (stats + 0x2C8));
  *((u32 *) (stats + 0x2CC)) = *((u32 *) (stats + 0x2D0));
  {
    unsigned int half = *((s16 *) (stats + 0x2D6));
    half = (s16) (inline_fn(half, half) >> 1);
    *((s16 *) (stats + 0x2D4)) = half;
  }
}
