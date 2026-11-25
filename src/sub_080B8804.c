/* Animation step: while the script action byte is above 7, start/advance
 * animation 0x1B, clear the linked object's state byte if the sprite's
 * animation word differs, and once the animator's bit 1 is set clear this
 * step's state/action bytes and advance the script. */
s32 sub_08011368(void *, s32, s32, s32);
s32 sub_080113A8(void *, s32);
s32 sub_080C31E8(void *, void *, s32, s32);
void sub_080B8804(void *arg0)
{
  s32 animState;
  s32 *scriptTable;
  void *work;
  void *sprite;
  sprite = *((void **) (((s8 *) arg0) + 0x38));
  work = *((void **) (((s8 *) arg0) + 0x3C));
  animState = work + 0x34;
  if (((u32) (*((u8 *) (((s8 *) (((*((s16 *) (((s8 *) arg0) + 0x22))) * 2) + arg0)) + 0x19)))) > 7U)
  {
    sub_08011368(sprite, animState, 0x1B, 0);
    sub_080113A8(sprite, animState);
    if ((*((u16 *) (((s8 *) sprite) + 0x28))) != 0x1B)
    {
      *((s8 *) (((s8 *) (*((void **) (((s8 *) arg0) + 0x28)))) + 0x4C)) = 0;
    }
    if (2 & (*((u8 *) (((s8 *) work) + 0x34))))
    {
      *((s8 *) (((s8 *) arg0) + 0x4C)) = 0;
      *((s8 *) (((s8 *) (((*((s16 *) (((s8 *) arg0) + 0x22))) * 2) + arg0)) + 0x19)) = 0;
      scriptTable = &(*((s32 *) 0x08671BD0));
      sub_080C31E8(arg0 + 0x18, arg0 + 0x22, 0, *scriptTable);
    }
  }
}
