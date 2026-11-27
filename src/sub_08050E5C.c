void sub_08051E94(void *, void *, s32, s32);
void setAnimationFrame(void *, void *, s32, s32);
void sub_08011460(void *, void *, s32);
void sub_080C31E4(void *, void *, void *);

extern void *gScriptStepCallbackTable;

/* Builds an 8-segment trail with a spread-dependent angle; once the script
 * step passes 0x3B it sets the animation and fires the script callback. */
void sub_08050E5C(void *arg0)
{
  u8 *self = (u8 *)arg0;
  void *sprite;
  u8 *work;
  u8 *animState;
  u8 *trail;
  s32 spread;
  s32 offsetScale;
  s32 step;
  s32 angle;

  sprite = *(void **)(self + 0x38);
  work = *(u8 **)(self + 0x3C);
  animState = work + 0x34;
  trail = work + 0xA0;

  spread = (s32)(s8)self[0x6C];
  offsetScale = ((spread << 3) - spread) << 11;

  step = *(s16 *)(self + 0x22);
  angle = ((self[step * 2 + 0x19] & 1) << 9);
  angle += 0xC000;
  angle -= offsetScale;

  sub_08051E94(self, trail, angle, 0x800);

  step = *(s16 *)(self + 0x22);
  if ((u32)self[step * 2 + 0x19] > 0x3B)
  {
    setAnimationFrame(sprite, animState, 0xA, 0);
    sub_08011460(sprite, animState, 0x20000);
    if (animState[0] & 2)
    {
      step = *(s16 *)(self + 0x22);
      self[step * 2 + 0x19] = 0;
      {
        void **fnaddr = &gScriptStepCallbackTable;
        sub_080C31E4(self + 0x18, self + 0x22, *fnaddr);
      }
    }
  }
}
