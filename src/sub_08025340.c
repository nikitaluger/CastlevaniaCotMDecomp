extern s32 sub_08014114(s32, s32, s32, s32, s32, s32);
extern void randomizeLaunchOffsets(void *, void *);
extern void _call_via_r2(void *, void *, s32);
inline int inline_fn(s16 arg0, int arg1)
{
  return arg0 * arg1;
}

/* If this entity's sub-object is active and visible on screen, launch it
 * (set its horizontal/vertical velocity), switch it to state 2 and restart
 * its animation. */
void sub_08025340(void *arg0)
{
  int zero;
  s32 posX;
  u8 *selfCopy;
  u8 *self = (u8 *) arg0;
  u8 *sub = *((u8 **) (self + 0x3C));
  u8 *state = sub + 0x48;
  if ((*((s16 *) state)) != 0)
  {
    selfCopy = self;
    posX = *((s32 *) (sub + 8));
    if (sub_08014114(posX, *((s32 *) (sub + 0xC)), -0x20, 0x20, -0x20, 0x20) != 0)
    {
      randomizeLaunchOffsets(sub + 0x50, sub + 0x54);
      zero = 0;
      *((u16 *) (state + 0x12)) = 2;
      *((u8 *)((u32)inline_fn(*((s16 *)(self + 0x22)), 2) + (u32)self) + 0x19) = zero;
      {
        s32 *animPtr = (s32 *) 0x08671BB0;
        _call_via_r2(selfCopy + 0x18, self + 0x22, *animPtr);
      }
    }
  }
}
