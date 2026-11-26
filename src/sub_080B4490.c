s32 sub_08005E80(s32);
s32 setObjectAnimation(s32, s32, s32, s32);
s32 sub_080B71CC(void *, s32, s32);
s32 sub_080C31E4(void *, void *, s32);

/* Attack step: play animation 0x52; 30 frames in, play sound 0x197, switch to
 * strike animation 0x5A, spawn a ring of six effects around a point 0x200000
 * above the actor and advance the script. */
void sub_080B4490(void *arg0)
{
  s32 sprite;
  void *work;
  s32 anim;
  s32 *cmdTable;

  sprite = *((s32 *) (((s8 *) arg0) + 0x38));
  work = *((void **) (((s8 *) arg0) + 0x3C));
  anim = work + 0x34;
  setObjectAnimation(sprite, anim, 0x52, 0);
  if ((*((u8 *) (((s8 *) (((*((s16 *) (((s8 *) arg0) + 0x22))) * 2) + arg0)) + 0x19))) == 0x1E)
  {
    sub_08005E80(0x197);
    setObjectAnimation(sprite, anim, 0x5A, 1);
    sub_080B71CC(arg0, *((s32 *) (((s8 *) work) + 8)), (*((s32 *) (((s8 *) work) + 0xC))) + 0xFFE00000);
    *((s8 *) (((s8 *) (((*((s16 *) (((s8 *) arg0) + 0x22))) * 2) + arg0)) + 0x19)) = 0;
    cmdTable = (s32 *) 0x08671BB0;
    sub_080C31E4(arg0 + 0x18, arg0 + 0x22, *cmdTable);
  }
}
