s32 setObjectAnimation(s32, s32, s32, s32);
s32 sub_08011528(s32, s32);
s32 sub_080C31E4(void *, void *, s32);

/* Effect-actor update: advance the animation to step 0x11 and tick it; while the
 * animation is active, shift the work value by +/-1.0 per the script byte. On
 * script step 0x3C reset the sprite fields, clear that byte and dispatch the
 * script-advance message. */
void sub_0809D6E4(void *arg0)
{
  s32 anim;
  s32 gfx;
  s32 value;
  void *sprite;
  s32 *lit;
  void *work;
  gfx = *((s32 *) (((s8 *) arg0) + 0x38));
  work = *((void **) (((s8 *) arg0) + 0x3C));
  anim = work + 0x34;
  sprite = work + 0x48;
  setObjectAnimation(gfx, anim, 0x11, 0);
  sub_08011528(gfx, anim);
  if (2 & (*((u8 *) (((s8 *) work) + 0x34))))
  {
    if (2 & (*((u8 *) (((s8 *) (((*((s16 *) (((s8 *) arg0) + 0x22))) * 2) + arg0)) + 0x19))))
    {
      value = (*((s32 *) (((s8 *) work) + 0xC))) + 0x10000;
    }
    else
    {
      value = (*((s32 *) (((s8 *) work) + 0xC))) + 0xFFFF0000;
    }
    *((s32 *) (((s8 *) work) + 0xC)) = value;
  }
  if ((*((u8 *) (((s8 *) (((*((s16 *) (((s8 *) arg0) + 0x22))) * 2) + arg0)) + 0x19))) == 0x3C)
  {
    *((s8 *) (((s8 *) sprite) + 0x3C)) = 0;
    *((s8 *) (((s8 *) sprite) + 0x14)) = 0;
    *((s8 *) (((s8 *) sprite) + 0x15)) = 0x28;
    *((s8 *) (((s8 *) (((*((s16 *) (((s8 *) arg0) + 0x22))) * 2) + arg0)) + 0x19)) = 0;
    lit = (s32 *) 0x08671BB0;
    sub_080C31E4(arg0 + 0x18, arg0 + 0x22, *lit);
  }
}
