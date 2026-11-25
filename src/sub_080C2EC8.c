/* memset: fill `count` bytes at `dest` with the low byte of `value`,
 * 4 bytes at a time while the destination is word aligned, then bytewise. */
u8 *sub_080C2EC8(u8 *dest, u32 value, u32 count)
{
  u8 *ptr = dest;
  if ((count > 3) && ((((u32) dest) & 3) == 0))
  {
    u32 *wordPtr = (u32 *) ptr;
    u32 pattern;
    value &= 0xFF;
    pattern = value | (value << 8);
    pattern |= pattern << 16;
    while (count > 15)
    {
      *(wordPtr++) = pattern;
      *(wordPtr++) = pattern;
      *(wordPtr++) = pattern;
      *(wordPtr++) = pattern;
      count -= 16;
    }

    while (count > 3)
    {
      *(wordPtr++) = pattern;
      count -= 4;
    }

    ptr = (u8 *) wordPtr;
  }
  while ((count--) > 0)
  {
    do
    {
      *(ptr++) = value;
    }
    while (0);
  }

  return dest;
}
