extern void setAnimationFrame(s32, void *, s32, s32);
extern s32 getSpriteFacingSign(void *);
extern void sub_080C31E8(void *, void *, s32, s32);

// Halts movement, chooses a facing-dependent speed for some poses, sets frame 5 and runs a step callback.
void sub_080427C8(void *arg0)
{
  u8 *sprite = *((u8 **) (((u8 *) arg0) + 0x38));
  u8 *physics = *((u8 **) (((u8 *) arg0) + 0x3C));
  u8 *animState = physics + 0x34;
  u8 *otherState = physics + 0x48;
  u16 pose;
  int frameId;
  s32 speed;
  void **callbackTable;
  *((s32 *) (physics + 0x14)) = 0;
  *((s32 *) (physics + 0x10)) = 0;
  pose = *((u16 *) (sprite + 0x28));
  frameId = 5;
  if (((u16) (pose - 0x10)) <= 4)
  {
    if (getSpriteFacingSign(sprite) > 0)
    {
      speed = *((s32 *) ((*((void **) (otherState + 0x10))) + 4));
    }
    else
    {
      speed = -(*((s32 *) ((*((void **) (otherState + 0x10))) + 4)));
    }
    *((s32 *) (physics + 0x10)) = speed;
  }
  setAnimationFrame((s32) sprite, animState, frameId, 0);
  if ((*animState) & 2)
  {
    (((u8 *) arg0) + ((*((s16 *) (((u8 *) arg0) + 0x22))) * 2))[0x19] = 0;
    callbackTable = (void **) 0x08671BD0;
    sub_080C31E8(((u8 *) arg0) + 0x18, ((u8 *) arg0) + 0x22, 0, (s32) (*callbackTable));
  }
}
