s32 sub_0803B140(s32, s32, s32, s32);
s32 sub_0803B194(s32);
void sub_080C31E4(void *, void *, s32);

/* Load the three graphic frame entries for the sprite's current key into the
 * slots at work+0x54, then advance to the next script step after 15 frames. */
void sub_080332F0(void *arg0)
{
  s32 sprite = *((s32 *) (((u8 *) arg0) + 0x38));
  s32 gfxSlots = (*((s32 *) (((u8 *) arg0) + 0x3C))) + 0x54;
  s32 *handlerTable;

  sub_0803B194(gfxSlots);
  sub_0803B140(7, sprite, gfxSlots, 0x080CED6E);
  if ((*((u8 *) (((u8 *) (((*((s16 *) (((u8 *) arg0) + 0x22))) * 2) + arg0)) + 0x19))) == 0xF)
  {
    *((u8 *) (((u8 *) (((*((s16 *) (((u8 *) arg0) + 0x22))) * 2) + arg0)) + 0x19)) = 0U;
    handlerTable = (s32 *) 0x08671BB0;
    sub_080C31E4((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, *handlerTable);
  }
}
