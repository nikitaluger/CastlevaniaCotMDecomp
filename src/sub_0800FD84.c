void sub_0800FEDC(s32 arg0, u16 *arg1);
s32 divideInt(s32, s32);
s32 moduloInt(s32, s32);
void drawDecimalNumber(s32 arg0, s32 arg1, u16 arg2, u16 *arg3);
void drawPaddedDecimal(s32 arg0, s32 arg1, u16 arg2, u16 *arg3);

/* Write the decimal digits of `value` right-to-left into `dst`, adding the u16
 * tile base and masking each digit down to a 10-bit tile index.  `unused` is
 * not read (it is the palette argument the sibling helpers take). */
void sub_0800FD84(s32 value, s32 unused, unsigned long tileBase, u16 *dst)
{
  s32 remaining = value;
  u16 *cursor = dst;
  u16 base = tileBase;
  u32 tileMask = 0x3FF;
  do
  {
    s32 digit = moduloInt(remaining, 10);
    remaining = divideInt(remaining, 10);
    *cursor = (base + digit) & tileMask;
    cursor--;
  }
  while (remaining != 0);
}
