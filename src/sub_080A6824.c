extern s32 sub_08005910(s32, s32);
void sub_080C31E0(void *, s32);
void sub_080C31E4(void *, void *, s32);
extern s32 D_08102094[][1];
extern s32 D_081020A4[];

/* Sets the actor's facing angle and a state value from the current script byte,
 * clears its other fields, then advances the script and dispatches the next handler. */
void sub_080A6824(void *arg0)
{
  u8 *self = (u8 *) arg0;
  u8 *actor = *((u8 **) (self + 0x3C));
  u8 *state = actor + 0x48;
  s32 deltaY = (*((s32 *) (state + 0x1C))) - (*((s32 *) (state + 0x08)));
  s32 deltaX = (*((s32 *) (state + 0x18))) - (*((s32 *) (state + 0x04)));
  s32 angle = sub_08005910(deltaY, deltaX);
  angle += D_08102094[(*((u8 *) (self + 0x4C))) * 2][1];
  angle &= 0xFFFF;
  do {
    *((s32 *) (actor + 0x10C)) = angle;
    *((s32 *) (actor + 0x118)) = D_081020A4[*((vu8 *) (self + 0x4C))];
    *((s32 *) (actor + 0x110)) = 0;
    *((u8 *) (actor + 0x120)) = 0;
    *((u8 *) ((self + ((*((s16 *) (self + 0x22))) * 2)) + 0x19)) = 0;
    {
      s32 *msgPtr = (s32 *) 0x08671BB0;
      u8 *step = self + 0x18;
      sub_080C31E4(step, self + 0x22, *msgPtr);
      *((u8 *) ((self + ((*((s16 *) (self + 0x22))) * 2)) + 0x19)) += 1;
      step += (*((s16 *) (self + 0x22))) * 2;
      sub_080C31E0(self, *((s32 *) ((*((u32 *) (self + 0x14))) + ((*((u8 *) step)) * 4))));
    }
  } while (0);
}
