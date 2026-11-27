void sub_080C31E4(void *, void *, s32);
void stepAnimationTrack(void *, void *);
s32 sub_080C31E0(void *, void *);

/* Sine bob: animate the linked body, then set its Y (body+0x0C) to the base Y
 * at self+0x8C minus twice the sine of the phase byte; when the phase reaches
 * 0x20 (half a revolution) reset it and advance the script. */
void sub_080B5BF8(void *arg0)
{
  u8 *self = arg0;
  s32 *sinTable;
  s32 sprite = *((s32 *) (self + 0x38));
  u8 *body = *((u8 **) (self + 0x3C));
  s32 sinOffset;
  s32 *table;
  stepAnimationTrack((void *) sprite, body + 0x34);
  sinTable = (s32 *) 0x08671BFC;
  table = sinTable;
  sinOffset = sub_080C31E0((void *) ((*((u8 *) ((self + ((*((s16 *) (self + 0x22))) * 2)) + 0x19))) << 11), (void *) (*table));
  *((s32 *) (body + 0x0C)) = (*((s32 *) (self + 0x8C))) - (sinOffset * 2);
  if ((*((u8 *) ((self + ((*((s16 *) (self + 0x22))) * 2)) + 0x19))) == 0x20)
  {
    *((u8 *) ((self + ((*((s16 *) (self + 0x22))) * 2)) + 0x19)) = 0;
    table = (s32 *) 0x08671BB0;
    sub_080C31E4(self + 0x18, self + 0x22, *table);
  }
}
