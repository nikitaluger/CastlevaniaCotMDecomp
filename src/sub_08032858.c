s32 setObjectAnimationFrame(s32, s32, s32, s32);
s32 checkActorViewBounds(s32);
s32 sub_080C31E4(void *, void *, s32);

/* Timed effect update: once it has lived 30 frames (and its parent does not
 * report the motion finished), it switches the sprite to animation 9 or 0x11
 * depending on the work flag 0x10, clears its step index and advances the
 * script. */
void sub_08032858(void *arg0)
{
  s32 fields[2];
  s32 anim;
  void *workCtl;
  fields[1] = *((s32 *) (((s8 *) arg0) + 0x38));
  fields[0] = *((s32 *) (((s8 *) arg0) + 0x3C));
  anim = fields[0] + 0x34;
  workCtl = (void *)(fields[0] + 0x48);
  if ((checkActorViewBounds(fields[1]) != 1) && (((u32) (*((u8 *) (((s8 *) (((*((s16 *) (((s8 *) arg0) + 0x22))) * 2) + arg0)) + 0x19)))) > 0x1EU))
  {
    s32 *scriptHandlers;
    if (0x10 & (*((u8 *) (((s8 *) workCtl) + 0xD))))
    {
      setObjectAnimationFrame(fields[1], anim, 9, 0);
    }
    else
    {
      setObjectAnimationFrame(fields[1], anim, 0x11, 0);
    }
    *((s8 *) (((s8 *) (((*((s16 *) (((s8 *) arg0) + 0x22))) * 2) + arg0)) + 0x19)) = 0;
    scriptHandlers = (s32 *)0x08671BB0;
    sub_080C31E4(arg0 + 0x18, arg0 + 0x22, *scriptHandlers);
  }
}
