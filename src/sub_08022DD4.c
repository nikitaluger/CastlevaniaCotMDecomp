extern s32 sub_08014114(s32, s32, s32, s32, s32, s32);
extern void sub_080C31E4(void *, void *, s32);

/* Deactivate this entity once it is on screen: if its sub-object is active
 * and its +/-0x30 box overlaps the visible area, clear its state word, hide
 * the sprite at the entity's tile index and run its animation callback. */
void sub_08022DD4(void *arg0)
{
  u8 *sub = *((u8 **) (((u8 *) arg0) + 0x3C));
  u8 *state = sub + 0x48;
  int zero;
  zero = 0;
  if ((*((s16 *) (state + 0x0A))) != zero)
  {
    if (sub_08014114(*((s32 *) (sub + 8)), *((s32 *) (sub + 0x0C)), -0x30, 0x30, -0x30, 0x30) != zero)
    {
      u8 *self = (u8 *) arg0;
      *((u16 *) (state + 0x0C)) = zero;
      *((u8 *) ((self + ((*((s16 *) (self + 0x22))) * 2)) + 0x19)) = zero;
      {
        void **animTable = (void **) 0x08671BB0;
        sub_080C31E4(self + 0x18, self + 0x22, (s32) (*animTable));
      }
    }
  }
}
