typedef s32 M2C_UNK;
M2C_UNK allocEffectPart();
M2C_UNK cleanupFailedEffectSpawn(void *);
M2C_UNK sub_0806DE0C();
M2C_UNK sub_080C31E8(void *, void *, s32, s32);
extern M2C_UNK releaseEffectGroup;
extern M2C_UNK sub_0807192C;
extern M2C_UNK sub_08071970;

// Allocates a child object for the entity, installs one of three update
// callbacks at +0x24 depending on the mode at +0x7C, then does the common
// setup (sound check, timer, per-slot flag clear) and calls the indirect
// callback from the 0x08671BD0 table with mode + 1.
void sub_0806E7E8(void *arg0)
{
  M2C_UNK *callback;
  s32 allocResult;
  M2C_UNK *callbackSlot;
  void *child;

  child = (*((s32 *) (((s8 *) arg0) + 0x6C))) + 4;
  allocResult = (*((s32 *) (((s8 *) child) + 0x3C)) = allocEffectPart());
  if (allocResult == 0)
  {
    cleanupFailedEffectSpawn(arg0);
    return;
  }
  if ((*((u16 *) (((s8 *) arg0) + 0x7C))) == 5)
  {
    if ((*((u16 *) (((s8 *) (arg0 + 0x7C)) + 8))) == 0)
    {
      *((M2C_UNK **) (((s8 *) child) + 0x18)) = (M2C_UNK *) (*((M2C_UNK **) (((s8 *) arg0) + 0x24)));
      callback = &sub_0807192C;
    }
    else
    {
      *((M2C_UNK **) (((s8 *) child) + 0x18)) = (M2C_UNK *) (*((M2C_UNK **) (((s8 *) arg0) + 0x24)));
      callback = &sub_08071970;
    }
  }
  else
  {
    *((M2C_UNK **) (((s8 *) child) + 0x18)) = (M2C_UNK *) (*((M2C_UNK **) (((s8 *) arg0) + 0x24)));
    callback = &releaseEffectGroup;
  }
  *((M2C_UNK **) (((s8 *) arg0) + 0x24)) = callback;
  sub_0806DE0C();
  *((s32 *) (((s8 *) child) + 0x10)) = 0xA;
  *((s8 *) (((s8 *) (((*((s16 *) (((s8 *) arg0) + 0x22))) * 2) + arg0)) + 0x19)) = 0;
  callback = (callbackSlot = (M2C_UNK *) 0x08671BD0);
  sub_080C31E8(arg0 + 0x18, arg0 + 0x22, (*((u16 *) (((s8 *) arg0) + 0x7C))) + 1, *callbackSlot);
}
