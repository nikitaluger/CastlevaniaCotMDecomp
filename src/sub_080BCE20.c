extern void sub_080114A8(void *sprite, void *animData, u16 anim, u8 arg);
extern void sub_080C31E0(void *arg, void *func);
extern void sub_080C31E4(void *stepData, void *stepIndex, s32 callback);
extern u32 gMainObjTimerCallback;
inline int inline_fn(u8 *arg0)
{
  return (*((s16 *) (arg0 + 0x22))) * 2;
}

/* Script step: while active, highlights the sprite, plays animation 0x1A, sets
 * a flag on each of the body's 50 part entries and advances the script by firing
 * its callback; when inactive, only clears the sprite highlight. */
void sub_080BCE20(void *arg0)
{
  u8 *self = (u8 *) arg0;
  u8 *sprite = *((u8 **) (self + 0x38));
  u8 *body = *((u8 **) (self + 0x3C));
  int highlightBits;
  u8 *animData = body + 0x34;
  u8 **parts = (u8 **) (body + 0x48);
  if ((*((s32 *) (self + 0x4C))) != 0)
  {
    u8 *stepData;
    u8 *stepIndex;
    u32 i;
    u8 **part;
    u32 *scriptCb;
    u8 stepCmd;
    u8 enabled;
    highlightBits = 0x40 | (*((u8 *) (sprite + 0x2A)));
    *((u8 *) (sprite + 0x2A)) = highlightBits;
    sub_080114A8(sprite, animData, 0x1A, 0);
    i = 0;
    stepData = self + 0x18;
    stepIndex = self + 0x22;
    enabled = 1;
    part = parts;
    do
    {
      (*(part++))[1] = enabled;
      i++;
    }
    while (i <= 0x31);
    *((u8 *) ((self + ((*((s16 *) (self + 0x22))) * 2)) + 0x19)) = 0;
    scriptCb = &gMainObjTimerCallback;
    sub_080C31E4(stepData, stepIndex, *scriptCb);
    (*((u8 *) ((self + ((*((s16 *) (self + 0x22))) * 2)) + 0x19)))++;
    stepCmd = *((u8 *) (stepData + inline_fn(self)));
    sub_080C31E0(self, *((void **) ((*((u8 **) (self + 0x14))) + (stepCmd * 4))));
  }
  else
  {
    *((u8 *) (sprite + 0x2A)) &= 0xBF;
  }
}
