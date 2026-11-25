extern void sub_080C31E0(void *, s32);
extern s32 sub_080C36E4(s32, s16);
extern void sub_08005E80(s32);

/* Increments the actor's counter each call: past the schedule's limit it fires
 * the callback at +0x24, and at each scheduled interval plays sound 0x1B1. */
void sub_08094C8C(void *actor)
{
  void *state = *((void **) (((u8 *) actor) + 0x3C));
  s32 count;
  if ((*((s32 *) state)) > (*((s16 *) ((*((u8 **) (((u8 *) state) + 4))) + 4))))
  {
    sub_080C31E0(actor, *((s32 *) (((u8 *) actor) + 0x24)));
  }
  if ((*((s32 *) state)) >= (*((s16 *) ((*((u8 **) (((u8 *) state) + 4))) + 0))))
  {
    s16 *schedule = *((s16 **) (((u8 *) state) + 4));
    if (sub_080C36E4((count = *((s32 *) state)) - schedule[0], schedule[1]) == 0)
    {
      sub_08005E80(0x1B1);
    }
 do { } while (0);
  }
  *((s32 *) state) += 1;
}
