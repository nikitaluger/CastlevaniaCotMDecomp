s32 sub_08005E80(s32);
s32 setObjectAnimation(s32, s32, s32, s32);
s32 sub_080C31E4(void *, void *, s32);

/* Script step: when the action byte is 0x14, play sound 0x164, set the sprite's
 * animation state, clear the action byte and advance the script. */
void sub_08099B14(void *self)
{
  s32 animator;
  s32 *workPtr;
  s32 *scriptHandlers;
  int stepIndex;
  s32 sprite;
  sprite = *((s32 *) (((s8 *) self) + 0x38));
  workPtr = (s32 *) (((s8 *) self) + 0x3C);
  animator = (*workPtr) + 0x34;
  if ((*((u8 *) (((s8 *) (((*((s16 *) (((s8 *) self) + 0x22))) * 2) + self)) + 0x19))) == 0x14)
  {
    sub_08005E80(0x164);
    setObjectAnimation(sprite, animator, 0x26, 0);
    stepIndex = *((s16 *) (((s8 *) self) + 0x22));
    *((s8 *) (((s8 *) ((stepIndex * 2) + self)) + 0x19)) = 0;
    scriptHandlers = (s32 *) 0x08671BB0;
    sub_080C31E4(self + 0x18, self + 0x22, *scriptHandlers);
  }
}
