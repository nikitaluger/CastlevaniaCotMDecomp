extern s32 updateObjectDisplayState(s32, u16 *);
extern void freeMotionTracker();

/* Applies an object's timed display state to its sprite attributes; while the
 * state is active it also clears two sprite-link flags and drops its effects. */
s32 sub_08050260(void *obj, s32 spriteAttrs)
{
  u16 *flags;
  s32 flagBits;
  void *link24;
  void *link20;
  void *state;
  flags = *((u16 **) (((s8 *) obj) + 0x3C));
  state = flags;
  state = state + 0x48;
  if (0xC & (*flags))
  {
    link20 = *((void **) (((s8 *) state) + 0x20));
    *((u8 *) (((s8 *) link20) + 1)) = (u8) (0xFE & (*((u8 *) (((s8 *) link20) + 1))));
    link24 = *((void **) (((s8 *) state) + 0x24));
    flagBits = 0;
    *((u8 *) (((s8 *) link24) + 1)) = (u8) (0xFE & (*((u8 *) (((s8 *) link24) + 1))));
    if (updateObjectDisplayState(spriteAttrs, flags) == 0)
    {
      return flagBits;
    }
    flagBits = 0xC & (*flags);
    if (flagBits == 0)
    {
      if ((*((s32 *) (((s8 *) state) + 0x28))) != 0)
      {
        freeMotionTracker();
        *((s32 *) (((s8 *) state) + 0x28)) = flagBits;
      }
      if ((*((s32 *) (((s8 *) state) + 0x2C))) != 0)
      {
        freeMotionTracker();
        *((s32 *) (((s8 *) state) + 0x2C)) = flagBits;
      }
    }
    return 1;
  }
  return updateObjectDisplayState(spriteAttrs, flags);
}
