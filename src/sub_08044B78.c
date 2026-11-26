s32 setAnimationFrame(s32, s32, s32, s32);
s32 sub_080113A8(s32, s32);
s32 sub_080C31E4(void *, void *, s32);

/* Per-frame actor update: advance the sprite animation; when its state's bit 1
 * is set, set the work vertical speed to -1.75, switch the animation to 0x15,
 * clear the current script step and jump to the next-step handler table. */
void sub_08044B78(void *actor)
{
  s32 *handlerTable;
  s32 state;
  s32 sprite;
  void *work;
  sprite = *((s32 *) (((s8 *) actor) + 0x38));
  work = *((void **) (((s8 *) actor) + 0x3C));
  state = work + 0x34;
  sub_080113A8(sprite, state);
  if (2 & (*((u8 *) (((s8 *) work) + 0x34))))
  {
    *((s32 *) (((s8 *) work) + 0x14)) = 0xFFFE4000;
    setAnimationFrame(sprite, state, 0x15, 0);
    *((s8 *) (((s8 *) (((*((s16 *) (((s8 *) actor) + 0x22))) * 2) + actor)) + 0x19)) = 0;
    handlerTable = (s32 *) 0x08671BB0;
    sub_080C31E4(actor + 0x18, actor + 0x22, *handlerTable);
  }
}
