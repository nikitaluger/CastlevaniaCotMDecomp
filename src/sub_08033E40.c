/* Enemy AI step: when the script action is 0x1E or the move-state flag at +0x10
 * is set, refresh the animation (frame 0x22 when flagged, 9 otherwise), then
 * clear the action byte and advance the script. */
s32 setObjectAnimationFrame(s32, s32, s32, s32);
s32 sub_080C31E4(void *, void *, s32);
void sub_08033E40(void *self)
{
  s32 *scriptTable;
  s32 sprite;
  s32 work;
  s32 animState;
  void *moveState;
  sprite = *((s32 *) (((s8 *) self) + 0x38));
  work = *((s32 *) (((s8 *) self) + 0x3C));
  animState = work + 0x34;
  moveState = work + 0x48;
  if (((*((u8 *) (((s8 *) (((*((s16 *) (((s8 *) self) + 0x22))) * 2) + self)) + 0x19))) == 0x1E) || (1 & (*((u8 *) (((s8 *) moveState) + 0x10)))))
  {
    if (1 & (*((u8 *) (((s8 *) moveState) + 0x10))))
    {
      setObjectAnimationFrame(sprite, animState, 0x22, 0);
    }
    else
    {
      setObjectAnimationFrame(sprite, animState, 9, 0);
    }
    *((s8 *) (((s8 *) (((*((s16 *) (((s8 *) self) + 0x22))) * 2) + self)) + 0x19)) = 0;
    scriptTable = (s32 *) 0x08671BB0;
    sub_080C31E4(self + 0x18, self + 0x22, *scriptTable);
  }
}
