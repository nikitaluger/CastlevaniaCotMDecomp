extern void sub_080C31E0(void *, void *);

/* Decrements the sub-object's countdown; on wrap-around fires the callback held
 * at +0x24, and while the count is small and a global flag is set, clears bit
 * 0x40 of a byte in the secondary object. */
void sub_0805E5BC(void *actor)
{
  s32 countCopy;
  u8 *self = (u8 *)actor;
  u8 *other = *((u8 **) (self + 0x38));
  u8 *sub = *((u8 **) (self + 0x3C));
  s32 count = (*((u16 *) (sub + 0x34))) - 1;
  *((u16 *) (sub + 0x34)) = count;
  count = (s16) count;
  countCopy = count;
  if (count < 0)
  {
    sub_080C31E0(self, *((void **) (self + 0x24)));
    return;
  }
  if (countCopy <= 0x77)
  {
    extern u8 D_02025FF0[];
    u8 *flags = D_02025FF0;
    flags += 0x189C;
    if ((*((u32 *) flags)) & 1)
    {
      u8 *flagByte = other + 0x2A;
      *flagByte &= 0xBF;
    }
  }
}
