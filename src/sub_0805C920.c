/* Dust-trail step: stop the effect body's horizontal velocity, give it a small
 * downward drift, spawn two particles below it every sixth frame, and after
 * 120 frames reset the script phase byte and advance the script. */
extern s32 sub_08014848(s32, s32, s32, s32, s32, s32);
extern void sub_080C31E4(void *, void *, s32);
extern u8 sub_080C389C(u8, s32);

void sub_0805C920(void *entity)
{
  void *work;
  void *stepEntry;
  s32 *stepTable;
  s32 stepOffset;

  work = *((void **) (((s8 *) entity) + 0x3C));
  *((s32 *) (((s8 *) work) + 0x10)) = 0;
  *((s32 *) (((s8 *) work) + 0x14)) = 0x8000;
  if (sub_080C389C(*((u8 *) (((s8 *) (((*((s16 *) (((s8 *) entity) + 0x22))) * 2) + entity)) + 0x19)), 6) == 1)
  {
    sub_08014848(1, 2, *((s32 *) (((s8 *) work) + 8)), (*((s32 *) (((s8 *) work) + 0xC))) + 0x100000, 0x120000, 0x40000);
  }

  stepOffset = (*((s16 *) (((s8 *) entity) + 0x22))) * 2;
  stepEntry = (void *)(stepOffset + (s32)entity);
  if (((u32) (*((u8 *) (((s8 *) stepEntry) + 0x19)))) > 0x78U)
  {
    *((u8 *) (((s8 *) stepEntry) + 0x19)) = 0U;
    stepTable = (s32 *) 0x08671BB0;
    sub_080C31E4(entity + 0x18, entity + 0x22, *stepTable);
  }
}
