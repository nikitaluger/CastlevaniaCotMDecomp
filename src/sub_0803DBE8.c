extern void setAnimationFrame(void *a, void *b, s32 c, s32 d);
extern s32 sub_08005820(s32 a);
extern s32 sub_08014990(void *a);
typedef void (*Fn)(void *, void *, s32);
void sub_0803DBE8(u8 *arg0)
{
  void *r7;
  u8 *r6;
  u8 *r4;
  u8 *r8;
  r7 = *((void **) (arg0 + 0x38));
  r6 = *((u8 **) (arg0 + 0x3C));
  r4 = r6 + 0x34;
  r8 = r6 + 0x48;
  setAnimationFrame(r7, r4, 0xD, 0);
  *((s32 *) (r6 + 0x10)) = 0;
  if ((*((u8 *) r4)) & 2)
  {
    if ((*((s16 *) (r8 + 2))) == 0)
    {
      s32 v = sub_08005820(0x97) + 0x1E;
      s32 zero = 0;
      *((s16 *) (r8 + 4)) = v | zero;
      *((u8 *) ((arg0 + ((*((s16 *) (arg0 + 0x22))) * 2)) + 0x17)) = zero;
      ((Fn) (*((void **) 0x08671BD8)))(arg0 + 0x18, arg0 + 0x22, 0);
    }
    else
    {
      if (sub_08014990(r7) > 0)
      {
        *((s32 *) (r6 + 0x10)) = 0xFFFEA000;
      }
      else
      {
        *((s32 *) (r6 + 0x10)) = 0x16000;
      }
      *((s32 *) (r6 + 0x14)) = 0xFFFE0000;
      *((u8 *) ((arg0 + ((*((s16 *) (arg0 + 0x22))) * 2)) + 0x19)) = 0;
      ((Fn) (*((void **) 0x08671BD0)))(arg0 + 0x18, arg0 + 0x22, 1);
    }
  }
}
