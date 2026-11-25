s32 sub_0801165C(void *, s32);
s32 sub_080C31E4(void *, void *, s32);
/* Fall/impact step: integrate the work object's position with gravity 0x5B0;
 * once it is moving downward, snap its y to the nearest pixel centre, record
 * that y at self+0x7C, clear the script substep and advance the script. */
void sub_080A4354(void *arg0)
{
  s32 snapY;
  void *work;
  s32 *scriptAdvance;
  work = *((void **) (((s8 *) arg0) + 0x3C));
  sub_0801165C(work, 0x5B0);
  if (((s32) (*((s32 *) (((s8 *) work) + 0x14)))) >= 0)
  {
    snapY = (((*((s32 *) (((s8 *) work) + 0xC))) + 0xFFFF8000) & 0xFFFF0000) | 0x8000;
    *((s32 *) (((s8 *) work) + 0xC)) = snapY;
    *((s32 *) (((s8 *) arg0) + 0x7C)) = snapY;
    *((s8 *) (((s8 *) (((*((s16 *) (((s8 *) arg0) + 0x22))) * 2) + arg0)) + 0x19)) = 0;
    scriptAdvance = (s32 *) 0x08671BB0;
    sub_080C31E4(arg0 + 0x18, arg0 + 0x22, *scriptAdvance);
  }
}
