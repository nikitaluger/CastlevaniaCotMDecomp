extern void setAnimationFrame(s32, void *, s32, s32);
extern s32 signedRemainder(s16, s32);
extern s32 divInt32(s16, s32);
extern s32 getSpriteFacingSign(s32);
extern void *sub_08024E4C(s32, s32, s32, s32, s32);
extern s32 (*gTrigFuncTable[])(s32);
extern void sub_080C31E4(void *, void *, u32);
inline static u8 *inline_fn(u8 *arg0)
{
  return arg0;
}

void sub_08024768(void *arg0)
{
  u8 *self = (u8 *) arg0;
  s32 sprite = *((s32 *) (self + 0x38));
  u8 *state = *((u8 **) (self + 0x3C));
  u8 *control = state + 0x48;
  u8 *anim = state + 0x34;
  s32 angle;
  s32 t;
  s32 x;
  s32 y;
  setAnimationFrame(sprite, anim, 9, 0);
  if (((u16) signedRemainder(*((s16 *) control), 10)) == 0)
  {
    if (getSpriteFacingSign(sprite) < 0)
    {
      angle = (u16) (((((u32) divInt32(*((s16 *) control), 10)) << 28) + 0x64000000) >> 16);
      t = (gTrigFuncTable[0](angle + 0x4000) << 4) + 0xFFEC0000;
    }
    else
    {
      angle = (u16) (0x1C00 - ((divInt32(*((s16 *) control), 10) << 16) >> 4));
      t = (gTrigFuncTable[0](angle + 0x4000) << 4) + 0x140000;
    }
    do
    {
      x = (*((s32 *) (state + 8))) + t;
    }
    while (0);
    do
    {
      y = ((gTrigFuncTable[0](angle) * 20) + 0xFFD80000) + (*((s32 *) (state + 0xC)));
    }
    while (0);
    sub_08024E4C(x, y, angle, *((s32 *) ((*((u8 **) (control + 8))) + 4)), *((s16 *) (state + 0x1c)));
  }
  *((u16 *) control) = (*((u16 *) control)) + 1;
  if ((*((u8 *) anim)) & 2)
  {
    {
      u16 __repair_narrow = 0;
      *((u16 *) control) = __repair_narrow;
    }
    if ((*((s16 *) (state + 0x1c))) == 0x46)
    {
      u32 cb;
      *((u8 *) ((self + ((*((s16 *) (((u8 *) arg0) + 0x22))) * 2)) + 0x17)) = 0;
      cb = *((u32 *) 0x08671BD8);
      ((void (*)(void *, void *, u32)) cb)(self + 0x18, self + 0x22, 0);
    }
    else
    {
      *((u8 *) ((self + ((*((s16 *) inline_fn(self + 0x22))) * 2)) + 0x19)) = 0;
      sub_080C31E4(self + 0x18, self + 0x22, *((u32 *) 0x08671BB0));
    }
  }
}

