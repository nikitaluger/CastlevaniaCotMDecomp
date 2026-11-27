s32 spawnJitteredParticles(s32, s32, s32, s32, s32, s32);
s32 sub_080C31E4(void *, void *, s32);
u8 sub_080C389C(u8, s32);   /* unsigned remainder helper: value % divisor */

/* Dust-trail step: give the effect body a slight downward velocity, spawn two
 * particles just below it every sixth frame (step byte % 6 == 1), and after
 * 120 frames reset the step's phase byte and advance the script. */
void sub_0801E530(void *entity)
{
  void *stepEntry;
  void *work;
  s32 *stepTable;

  work = *((void **) (((s8 *) entity) + 0x3C));
  *((s32 *) (((s8 *) work) + 0x10)) = 0;
  *((s32 *) (((s8 *) work) + 0x14)) = 0x8000;
  if (sub_080C389C(*((u8 *) (((s8 *) (((*((s16 *) (((s8 *) entity) + 0x22))) * 2) + entity)) + 0x19)), 6) == 1)
  {
    spawnJitteredParticles(1, 2, *((s32 *) (((s8 *) work) + 8)), (*((s32 *) (((s8 *) work) + 0xC))) + 0x80000, 0xE0000, 0x100000);
  }
  stepEntry = ((*((s16 *) (((s8 *) entity) + 0x22))) * 2) + entity;
  if (((u32) (*((u8 *) (((s8 *) (((*((s16 *) (((s8 *) entity) + 0x22))) * 2) + entity)) + 0x19)))) > 0x78U)
  {
    *((u8 *) (((s8 *) (((*((s16 *) (((s8 *) entity) + 0x22))) * 2) + entity)) + 0x19)) = 0U;
    stepTable = &(*((s32 *) 0x08671BB0));
    sub_080C31E4(entity + 0x18, entity + 0x22, *stepTable);
  }
}
