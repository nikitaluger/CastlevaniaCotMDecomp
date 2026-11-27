s32 setAttachedObjectMode(s32, s32, s32);
u32 divideInt(u8, s32);

/* Pick a phase from the current script slot's byte: divide it by 6, clamp it to
 * 2 and invert it. Store the phase on the object and mirror it into the sprite
 * state byte (5 when non-zero), unless the shared block already reports state 1. */
s32 sub_080BBA08(void *arg0)
{
  s8 *base;
  s32 phase;
  s32 ctrl;
  u32 quotient;
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
  quotient = 2 - quotient;
  phase = quotient;
  base = (s8 *) work;
  setAttachedObjectMode(*((s32 *) (base + 0x20)), phase, ctrl);
  return phase;
}
