s32 sub_08014848(s32, s32, s32, s32, s32, s32);
s32 sub_080C31E4(void *, void *, s32);
u8 sub_080C389C(u8, s32);   /* unsigned remainder helper: value % divisor */

/* Dust-trail variant that hangs in place: clear the effect body's velocity,
 * spawn two particles just above it every sixth frame (step byte % 6 == 1),
 * and after 90 frames reset the step's phase byte and advance the script. */
void sub_08024A34(void *entity)
{
  void *stepEntry;
  s32 *stepPtr;   /* at the step index word first, then reused for the step table */
  void *work;

  work = *((void **) (((s8 *) entity) + 0x3C));
  *((s32 *) (((s8 *) work) + 0x10)) = 0;
  stepPtr = ((s8 *) entity) + 0x22;
  *((s32 *) (((s8 *) work) + 0x14)) = 0;
  if (sub_080C389C(*((u8 *) (((s8 *) (((*((s16 *) stepPtr)) * 2) + entity)) + 0x19)), 6) == 1)
  {
    sub_08014848(1, 2, *((s32 *) (((s8 *) work) + 8)), (*((s32 *) (((s8 *) work) + 0xC))) + 0xFFF40000, 0xE0000, 0x140000);
  }
  stepEntry = ((*((s16 *) stepPtr)) * 2) + entity;
  if (((u32) (*((u8 *) (((s8 *) (((*((s16 *) stepPtr)) * 2) + entity)) + 0x19)))) > 0x5AU)
  {
    *((u8 *) (((s8 *) (((*((s16 *) stepPtr)) * 2) + entity)) + 0x19)) = 0U;
    stepPtr = &(*((s32 *) 0x08671BB0));
    sub_080C31E4(entity + 0x18, entity + 0x22, *stepPtr);
  }
}
