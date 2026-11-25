void sub_080BB984(void *, void *);
void sub_080988B8(void *, s32);
void sub_080BBA08(void *);
void sub_080C31E4(void *, void *, s32);

/* Walk tick: advance the body bob, turn to face the direction of travel, pick
 * the next pose, and at script step 0x18 clear it and advance the script. */
void sub_080BAFC4(void *arg0)
{
  u8 *self = (u8 *) arg0;
  void *bodyBase;
  s32 animState;
  u8 *control;
  u8 *self2;
  s32 *stepTable;
  bodyBase = *((void **) (self + 0x3C));
  control = ((u8 *) bodyBase) + 0x48;
  animState = *((s32 *) (self + 0x4C));
  sub_080BB984(bodyBase, control);
  sub_080988B8((void *) animState, *((s32 *) (((u8 *) bodyBase) + 0x08)));
  sub_080BBA08(arg0);
  if ((*((u8 *) ((self + ((*((s16 *) (self + 0x22))) * 2)) + 0x19))) == 0x18)
  {
    *((u8 *) ((self + ((*((s16 *) (self + 0x22))) * 2)) + 0x19)) = 0;
    stepTable = (s32 *) 0x08671BB0;
    sub_080C31E4(self + 0x18, (self2 = self) + 0x22, *stepTable);
  }
}
