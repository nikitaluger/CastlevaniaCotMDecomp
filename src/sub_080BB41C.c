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
M2C_UNK sub_080BB8AC(void *);
M2C_UNK sub_080BB940(s32, s32);
M2C_UNK sub_080BE8D0(s32, s32);
M2C_UNK sub_080C31E8(void *, void *, s32, s32);
inline s32 loadWord(s32 arg0)
{
  return *((s32 *) arg0);
}

/* Actor script step: refresh a linked object's facing, clear its pointer flags,
 * then either finish immediately when the object's finish flag is set, or count
 * down a timer and dispatch a script continuation when the timer expires. */
void sub_080BB41C(void *arg0)
{
  s32 body;
  s32 counter;
  s32 litBD8;
  s32 *zeroPtr;
  s32 count;
  void *work;
  body = *((s32 *) (((s8 *) arg0) + 0x3C));
  work = body + 0x48;
  sub_080BB940(body, *((s32 *) (((s8 *) arg0) + 0x4C)));
  do
  {
    sub_080BB8AC(work);
  }
  while (0)
  ;
  if ((*((s32 *) (((s8 *) work) + 0x4C))) == 0)
  {
    *((s8 *) (((s8 *) (((*((s16 *) (((s8 *) arg0) + 0x22))) * 2) + arg0)) + 0x17)) = (s8) (*((s32 *) (((s8 *) work) + 0x4C)));
    litBD8 = 0x08671BD8;
    sub_080C31E8(arg0 + 0x18, arg0 + 0x22, 1, loadWord(litBD8));
    return;
  }
  counter = (*((s32 *) (((s8 *) work) + 0x40))) + 0xFFFFFA00;
  *((s32 *) (((s8 *) work) + 0x40)) = counter;
  if (counter < 0)
  {
    *((s32 *) (((s8 *) work) + 0x40)) = 0;
  }
  sub_080BE8D0(*((s32 *) (((s8 *) work) + 0x34)), *((s32 *) (((s8 *) work) + 0x40)));
  count = *((s32 *) (((s8 *) work) + 0x40));
  if (count == 0)
  {
    zeroPtr = &count;
    *((s8 *) (((s8 *) (((*((s16 *) (((s8 *) arg0) + 0x22))) * 2) + arg0)) + 0x19)) = (s8) (*zeroPtr);
    count = 0x08671BD0;
    sub_080C31E8(arg0 + 0x18, arg0 + 0x22, 1, loadWord(*zeroPtr));
  }
}
