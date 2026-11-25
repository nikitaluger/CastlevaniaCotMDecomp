extern void sub_080114DC(void *, void *, s32, s32);
extern void sub_08011528(void *, void *);
extern void sub_080C31E8(void *, void *, s32, s32);
extern s16 D_08102B78[];
inline u8 *inline_fn(u8 *arg0)
{
  return arg0;
}

/* Entity update: choose the animation for the actor's pose index (actor+0x68)
 * from table D_08102B78, advance it, then move to the next state (function
 * pointer at 0x08671BD0) when pose 0 reaches local state 4, or when the
 * animation's flag byte has bit 1 set. */
void sub_080B3B48(void *arg0)
{
  u8 *self = arg0;
  u8 *gfx = *((u8 **) (self + 0x38));
  u8 *actor = *((u8 **) (self + 0x3C));
  u8 *anim = actor + 0x34;
  s32 *nextState[2];
  sub_080114DC(gfx, anim, D_08102B78[*(actor + 0x68)], 0);
  sub_08011528(gfx, anim);
  if (*(actor + 0x68) == 0)
  {
    u8 *stateSlot = (u8 *) ((((s32) (*((s16 *) (self + 0x22)))) * 2) + ((s32) self));
    if (stateSlot[0x19] == 4)
    {
      stateSlot[0x19] = 0;
      nextState[0] = (s32 *) 0x08671BD0;
      nextState[1] = self + 0x18;
      sub_080C31E8(nextState[1], self + 0x22, 1, *nextState[0]);
      return;
    }
  }
  if (((*anim) & 2) != 0)
  {
    u8 *stateSlot = (u8 *) ((((s32) (*((s16 *) (self + 0x22)))) * 2) + ((s32) self));
    stateSlot[0x19] = 0;
    nextState[0] = (s32 *) 0x08671BD0;
    nextState[1] = self + 0x18;
    sub_080C31E8(nextState[1], inline_fn(self) + 0x22, 1, *nextState[0]);
  }
}
