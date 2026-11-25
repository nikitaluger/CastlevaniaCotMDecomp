/* Effect update: clears two velocity words in its work state, emits a puff of
 * two particles every sixth frame just above its position, and after 90 frames
 * resets the frame counter and advances the script. */
#ifndef M2C_DEFINES
#define M2C_DEFINES
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
#define M2C_BITWISE(type, expr) ((type)(expr))
#define M2C_ERROR(desc) (0)
#define M2C_CARRY 0
#define M2C_OVERFLOW(a) (0)
#endif
typedef s32 M2C_UNK;
typedef s8 M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;
M2C_UNK sub_08014848(s32, s32, s32, s32, s32, s32);
M2C_UNK sub_080C31E4(void *, void *, s32);
u8 sub_080C389C(u8, s32); /* unsigned remainder */
void sub_0804E34C(void *arg0)
{
  void *temp_r1;
  s32 *tmpPtr;
  void *work;
  work = *((void **) (((s8 *) arg0) + 0x3C));
  *((s32 *) (((s8 *) work) + 0x10)) = 0;
  tmpPtr = ((s8 *) arg0) + 0x22;
  *((s32 *) (((s8 *) work) + 0x14)) = 0;
  if (sub_080C389C(*((u8 *) (((s8 *) (((*((s16 *) tmpPtr)) * 2) + arg0)) + 0x19)), 6) == 1)
  {
    sub_08014848(1, 2, *((s32 *) (((s8 *) work) + 8)), (*((s32 *) (((s8 *) work) + 0xC))) + 0xFFFC0000, 0x180000, 0x80000);
  }
  temp_r1 = ((*((s16 *) tmpPtr)) * 2) + arg0;
  if (((u32) (*((u8 *) (((s8 *) (((*((s16 *) tmpPtr)) * 2) + arg0)) + 0x19)))) > 0x5AU)
  {
    *((u8 *) (((s8 *) (((*((s16 *) tmpPtr)) * 2) + arg0)) + 0x19)) = 0U;
    tmpPtr = &(*((s32 *) 0x08671BB0));
    sub_080C31E4(arg0 + 0x18, arg0 + 0x22, *tmpPtr);
  }
}
