extern s32 sub_08014848(s32, s32, s32, s32, s32, s32);
extern void sub_080C31E0(void *, s32);
extern u8 sub_080C389C(u8, s32);
/* work+0x14 (the work state's y velocity), work+0x10 and the patrol counter at
 * work+0x4C are zeroed. If the script-action byte mod 6 is 1, spawn one particle
 * at the work position; if the byte exceeds 0x3C, abort the script. */
inline s8 *workPlus14(void *arg0)
{
  return ((s8 *) arg0) + 0x14;
}

void sub_0804284C(void *obj)
{
  s8 *patrol;
  s32 xPos;
  void *work;
  work = *((void **) (((s8 *) obj) + 0x3C));
  patrol = (s8 *) (work + 0x48);
  *((s16 *) (patrol + 4)) = (*((s32 *) (((s8 *) work) + 0x10)) = (*((s32 *) workPlus14(work)) = 0));
  if (sub_080C389C(*((u8 *) (((s8 *) (((*((s16 *) (((s8 *) obj) + 0x22))) * 2) + obj)) + 0x19)), 6) == 1)
  {
    xPos = *((s32 *) (((s8 *) work) + 8));
    sub_08014848(1, 1, xPos, (*((s32 *) (0xC + ((s8 *) work)))) + 0xFFF00000, 0xE0000, 0x100000);
  }
  if (((u32) (*((u8 *) (((s8 *) (((*((s16 *) (((s8 *) obj) + 0x22))) * 2) + obj)) + 0x19)))) > 0x3CU)
  {
    sub_080C31E0(obj, *((s32 *) (((s8 *) obj) + 0x24)));
  }
}
