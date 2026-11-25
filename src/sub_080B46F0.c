void sub_08005E80(s32 soundId);
void sub_080114DC(s32 sprite, s32 animState, s32 frame, s32 arg3);
void sub_08011528(s32 sprite, s32 animState);
void sub_080C31E4(void *scriptData, void *scriptIndex, s32 handler);

/* Plays animation frame 0x1C; once that frame has finished, plays sound 0x196,
 * launches the actor upward (zero X velocity, -1.0 Y velocity), clears the
 * current script action byte and advances the script. */
void sub_080B46F0(void *arg0)
{
  s32 animState;
  unsigned int sprite;
  s32 *scriptTable;
  void *work;
  sprite = *((s32 *) (((u8 *) arg0) + 0x38));
  work = *((void **) (((u8 *) arg0) + 0x3C));
  animState = work + 0x34;
  sub_080114DC(sprite, animState, 0x1C, 0);
  sub_08011528(sprite, animState);
  if (2 & (*((u8 *) (((u8 *) work) + 0x34))))
  {
    sub_08005E80(0x196);
    *((s32 *) (((u8 *) work) + 0x10)) = 0;
    *((s32 *) (((u8 *) work) + 0x14)) = 0xFFFF0000;
    *((u8 *) (((u8 *) (((*((s16 *) (((u8 *) arg0) + 0x22))) * 2) + (u8 *) arg0)) + 0x19)) = 0;
    scriptTable = (s32 *) 0x08671BB0;
    sub_080C31E4(arg0 + 0x18, arg0 + 0x22, *scriptTable);
  }
}
