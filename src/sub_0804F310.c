s32 absXFromFocus(s32);
s32 absYFromFocus(s32);
s32 signOf(s32);
s32 sub_08014964(s32);
s32 sub_08014990(s32);
s32 sub_080C31E4(void *, void *, s32);

/* If the view entity faces the target and the target lies within range of the
 * screen bounds, restarts the target's animation. */
void sub_0804F310(void *self)
{
  s32 view;
  s32 facing;
  s32 dist;
  void *target;
  s8 *yPtr;
  s32 *frameRoutine;
  view = *((s32 *) (((s8 *) self) + 0x38));
  target = *((void **) (((s8 *) self) + 0x3C));
  if (sub_08014964(*((s32 *) (((s8 *) target) + 0xC))) >= 0)
  {
    facing = sub_08014990(view);
    if (facing == signOf(*((s32 *) (((s8 *) target) + 8))))
    {
      yPtr = ((s8 *) target) + 0xC;
      dist = absXFromFocus(*((s32 *) (((s8 *) target) + 8)));
      if (dist <= absYFromFocus(*((s32 *) yPtr)))
      {
        if (1)
        {
          *((s8 *) (((s8 *) (((*((s16 *) (((s8 *) self) + 0x22))) * 2) + self)) + 0x19)) = 0;
          frameRoutine = (s32 *) 0x08671BB0;
          sub_080C31E4(self + 0x18, self + 0x22, *frameRoutine);
        }
      }
    }
  }
}
