s32 sub_080AC9B4(u8, void *);
s32 sub_080C31E4(void *, void *, s32);
/* Rising particle-emitter state: spawn the periodic random effect for emitter
 * type work+0x244, drift the work object up 0x1000 per frame, and once its y
 * reaches 0x680000 clamp it there, clear the script substep and advance. */
void sub_080AC220(void *arg0)
{
  s32 *scriptAdvance;
  s32 y;
  void *work;
  work = *((void **) (((s8 *) arg0) + 0x3C));
  sub_080AC9B4(*((u8 *) (((s8 *) work) + 0x244)), work + 0x68);
  y = (*((s32 *) (((s8 *) work) + 0xC))) + 0xFFFFF000;
  *((s32 *) (((s8 *) work) + 0xC)) = y;
  if (y <= 0x67FFFF)
  {
    *((s32 *) (((s8 *) work) + 0xC)) = 0x680000;
    *((s8 *) (((s8 *) (((*((s16 *) (((s8 *) arg0) + 0x22))) * 2) + arg0)) + 0x19)) = 0;
    scriptAdvance = (s32 *) 0x08671BB0;
    sub_080C31E4(arg0 + 0x18, arg0 + 0x22, *scriptAdvance);
  }
}
