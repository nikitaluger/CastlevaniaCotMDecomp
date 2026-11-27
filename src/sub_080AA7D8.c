s32 setAnimationFrame(s32, s32, s32, s32);
void computePosePlacementOffset(void *, s32);
s32 sub_080C31E4(void *, void *, s32);

/* Refresh the child sprite's pose-based position; when the current script
 * step's state byte reaches 4, switch that sprite to animation frame 10,
 * clear the state and advance the script. */
void sub_080AA7D8(void *entity)
{
  u8 *self = (u8 *)entity;
  s32 sprite;
  s32 motion;
  s32 status;
  s32 *advance;
  sprite = *(s32 *)(self + 0x38);
  motion = *(s32 *)(self + 0x3C);
  status = motion + 0x34;
  computePosePlacementOffset(entity, motion);
  if (*(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) == 4)
  {
    setAnimationFrame(sprite, status, 0xA, 0);
    *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
    advance = (s32 *)0x08671BB0;
    sub_080C31E4(self + 0x18, self + 0x22, *advance);
  }
}
