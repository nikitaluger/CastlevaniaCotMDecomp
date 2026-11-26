extern void setAnimationFrame(void *, void *, s32, s32);
extern void sub_080C050C(s32);
extern void sub_080C31E4(void *, void *, s32);
extern s16 D_08100B1C[];      /* animation index per part kind */
extern u8 D_0866FAFC;         /* part handler pointer table (4 bytes per kind) */
extern u8 D_08100B1E;         /* part parameter table (2 bytes per kind) */

/* Advances a part's animation; once its timer passes the limit, plays a cue,
 * resets the timer and flags, loads the next handler/parameter for this part
 * kind, and advances the actor's script step. */
void sub_080963F4(void *arg0)
{
  u8 *self = arg0;
  u8 *sprite = *((u8 **) (self + 0x38));
  u8 *work = *((u8 **) (self + 0x3C));
  u8 *animState = work + 0x34;
  u8 *parts = work + 0x48;
  s16 animIndex = D_08100B1C[*((s32 *) (work + 0x48))];
  setAnimationFrame(sprite, animState, animIndex, 1);
  if ((*((s32 *) (work + 0x08))) > 0x024FFFFF) {
    sub_080C050C(0x1BE);
    *((s32 *) (work + 0x08)) = 0x02500000;
    *((s32 *) (work + 0x10)) = 0;
    *((u16 *) (parts + 0x12)) = 0;
    *((u16 *) (parts + 0x14)) = 6;
    {
      u8 *handlerTable = &D_0866FAFC;
      s32 entryOffset = (*((s32 *) (work + 0x48))) << 2;
      *((u32 *) (sprite + 0x24)) = *((u32 *) (handlerTable + entryOffset));
      *((u16 *) (sprite + 0x28)) = *((u16 *) (&D_08100B1E + entryOffset));
    }
    *((u8 *) ((self + ((*((s16 *) (self + 0x22))) * 2)) + 0x19)) = 0;
    {
      s32 *lit = (s32 *) 0x08671BB0;
      sub_080C31E4(self + 0x18, self + 0x22, *lit);
    }
  }
}
