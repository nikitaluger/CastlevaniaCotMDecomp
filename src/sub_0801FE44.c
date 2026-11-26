s32 setAnimationFrame(s32, s32, s32, s32);
s32 sub_080146D0(void *, s32, s32);
s32 sub_080C31E4(void *, void *, s32);

/* Update an effect's animation, then, when flag bit 0 of self+0x5C is set,
 * set its target position via sub_080146D0 using an angle chosen by bit 0x10,
 * clear the step flag and advance the script. */
void sub_0801FE44(void *arg0)
{
  u8 *self = (u8 *)arg0;
  s32 sprite = *((s32 *)(self + 0x38));
  void *body = *((void **)(self + 0x3C));
  u8 *anim = (u8 *)body + 0x34;
  u8 *part = (u8 *)body + 0x48;
  u16 v;
  s32 angle;
  if ((*((s32 *)(part + 4))) == 0)
  {
    setAnimationFrame(sprite, (s32)anim, 0xB, 0);
    if (2 & (*anim))
    {
      *((s32 *)(part + 4)) = 1;
    }
  }
  else
  {
    setAnimationFrame(sprite, (s32)anim, 0x11, 1);
  }
  ;
  if (1 & (*((u16 *)(self + 0x5C))))
  {
    if ((*((u16 *)(self + 0x5C))) & 0x10)
    {
      angle = 0x6000;
    }
    else
    {
      angle = 0x2000;
    }
    sub_080146D0(body, angle, *((s32 *)(self + 0x6C)));
    *((u8 *)(self + ((*((s16 *)(self + 0x22))) * 2) + 0x19)) = 0;
    {
      s32 *lit = (s32 *)0x08671BB0;
      sub_080C31E4(self + 0x18, self + 0x22, *lit);
    }
  }
}
