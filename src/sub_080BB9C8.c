s32 setAttachedObjectMode(s32, u32, s32);
u32 divideInt(u8, s32);

/* Pick a phase from the current script slot's byte: divide it by 6 and clamp it
 * to 2, then store it on the object and mirror it into the sprite state byte,
 * unless the shared block already reports state 1. */
u32 sub_080BB9C8(void *arg0)
{
  s8 *base;
  u32 quotient;
  s32 ctrl;
  void *work;
  ctrl = *((s32 *) (((s8 *) arg0) + 0x3C));
  work = ctrl + 0x48;
  if ((*((s32 *) (((s8 *) work) + 0x3C))) == 1)
  {
    return 0;
  }
  quotient = (unsigned int) divideInt(*((u8 *) (((s8 *) (((*((s16 *) (((s8 *) arg0) + 0x22))) * 2) + arg0)) + 0x19)), 6);
  if (quotient > 2U)
  {
    quotient = 2;
  }
  base = (s8 *) work;
  setAttachedObjectMode(*((s32 *) (base + 0x20)), quotient, ctrl);
  return quotient;
}
