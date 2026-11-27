s32 sub_080A860C(void *, s32);
s32 decelerateTargetX(s32, s32);
s32 sub_080C31E4(void *, void *, s32);

/* Updates the entity's pose, then when the work flag at +0x120 is set and the
 * state value at +0x110 is zero, clears the action byte and advances the
 * script step. */
void sub_080A6444(void *arg0)
{
  s32 pose;
  s32 stateValue;
  s32 sprite;
  void *work;
  s32 *scriptHandlers;
  sprite = *((s32 *) (((s8 *) arg0) + 0x38));
  work = *((void **) (((s8 *) arg0) + 0x3C));
  pose = work + 0x48;
  sub_080A860C(arg0, pose);
  decelerateTargetX(sprite, pose);
  if ((*((u8 *) (((s8 *) work) + 0x120))) != 0)
  {
    stateValue = *((s32 *) (((s8 *) work) + 0x110));
    if (stateValue == 0)
    {
      *((s8 *) (((s8 *) (((*((s16 *) (((s8 *) arg0) + 0x22))) * 2) + arg0)) + 0x19)) = (s8) stateValue;
      scriptHandlers = &(*((s32 *) 0x08671BB0));
      sub_080C31E4(arg0 + 0x18, arg0 + 0x22, *scriptHandlers);
    }
  }
}
