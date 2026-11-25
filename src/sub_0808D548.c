extern s32 sub_0808D690(s32, void *, s32);
extern s32 sub_0808D6C4(s32, void *);

/* Advance the second phase of a scripted effect: tick its timers, publish its angles
 * to the global angle table, ramp its sub-object velocities, then switch to the next
 * update function once the timer expires. */
void sub_0808D548(u8 *effect)
{
  u8 *fx = *((u8 **) (effect + 0x6C));
  s32 angle;
  u8 *angleTable;
  u32 off;

  *((s32 *) (fx + 0x34)) = (*((s32 *) (fx + 0x34))) + 1;
  *((u8 *) (fx + 0x39)) = (*((u8 *) (fx + 0x39))) + 1;
  *((u8 *) (fx + 0x3A)) = (*((u8 *) (fx + 0x3A))) + 1;

  angleTable = (u8 *) 0x02021E90;
  angle = *((s16 *) (fx + 6));
  off = 0x1460;
  *((s8 *) (angleTable + off)) = angle;
  angle = *((s16 *) (fx + 0x16));
  off = 0x1464;
  *((s8 *) (angleTable + off)) = angle;
  angle = *((s16 *) (fx + 0x0E));
  off = 0x1462;
  *((s8 *) (angleTable + off)) = angle;
  angle = *((s16 *) (fx + 0x1E));
  off = 0x1466;
  *((s8 *) (angleTable + off)) = angle;
  *((s8 *) (angleTable + 0x1468)) = 0x31;

  sub_0808D6C4(1, fx);
  sub_0808D690(0, fx + 8, *((s32 *) (fx + 0x28)));
  sub_0808D690(1, fx + 0x10, *((s32 *) (fx + 0x28)));
  sub_0808D690(0, fx + 4, *((s32 *) (fx + 0x24)));
  sub_0808D690(1, fx + 0x0C, *((s32 *) (fx + 0x24)));

  if ((*((s32 *) (fx + 0x34))) > 0x38)
  {
    *((u16 *) (effect + 0x22)) = 0;
    *((s32 *) (effect + 0x14)) = 0x0808D5F1;
  }
}
