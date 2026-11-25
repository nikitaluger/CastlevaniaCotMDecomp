s32 sub_0803B194(s32);
s32 sub_0803B1A4(s32);
void sub_080C31E8(void *, void *, s32, s32);

/* Mark the three graphic slots at work+0x54 as loaded and, after 30 frames,
 * release them and advance to the next script step. */
void sub_08034D4C(void *arg0)
{
  s32 gfxSlots = (*((s32 *) (((u8 *) arg0) + 0x3C))) + 0x54;
  s32 *handlerTable;

  sub_0803B194(gfxSlots);
  if ((*((u8 *) (((u8 *) (((*((s16 *) (((u8 *) arg0) + 0x22))) * 2) + arg0)) + 0x19))) == 0x1E)
  {
    sub_0803B1A4(gfxSlots);
    *((s8 *) (((u8 *) (((*((s16 *) (((u8 *) arg0) + 0x22))) * 2) + arg0)) + 0x19)) = 0;
    handlerTable = &(*((s32 *) 0x08671BD0));
    sub_080C31E8((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, 0, *handlerTable);
  }
}
