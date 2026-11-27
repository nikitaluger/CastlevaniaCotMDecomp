void stepAnimationTrack(s32, s32);
void sub_080C31E8(void *, void *, s32, s32);
void sub_08032A04(void *arg0)
{
  void *r0 = *((void **) (((u8 *) arg0) + 0x38));
  void *r4 = *((void **) (((u8 *) arg0) + 0x3C));
  s32 *lit;
  s32 *callbackTable;
  u8 *p18;
  stepAnimationTrack((s32) (*((u32 *) (&r0))), (s32) (((u8 *) r4) + 0x34));
  if ((2 & (*((u8 *) (((u8 *) r4) + 0x34)))) || (*((u8 *) (((u8 *) arg0) + 0x80))))
  {
    *((u8 *) ((((u8 *) arg0) + (((int) (*((s16 *) (((u8 *) arg0) + 0x22)))) * 2)) + 0x19)) = 0;
    callbackTable = (s32 *) 0x08671BD0;
    p18 = ((u8 *) arg0) + 0x18;
    lit = ((u8 *) arg0) + 0x22;
    sub_080C31E8(p18, lit, 0, *callbackTable);
  }
}
