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
M2C_UNK sub_08005E80(s32);
M2C_UNK sub_08011368(s32, s32, s32, s32);
M2C_UNK sub_08011460(s32, s32, s32);
M2C_UNK sub_080C31E4(void *, void *, s32);

/* Set up the sprite's animation from the work state; when the animator's
 * phase byte has bit 1 set, play sound 0x183 and advance the script. */
void sub_080B7FA4(void *arg0)
{
  s32 anim;
  s32 *callback;
  s32 sprite;
  void *work;
  sprite = *((s32 *) (((s8 *) arg0) + 0x38));
  work = *((void **) (((s8 *) arg0) + 0x3C));
  anim = work + 0x34;
  sub_08011368(sprite, anim, 2, 0);
  sub_08011460(sprite, anim, 0x40000);
  if (2 & (*((u8 *) (((s8 *) work) + 0x34))))
  {
    sub_08005E80(0x183);
    *((s8 *) (((s8 *) (((*((s16 *) (((s8 *) arg0) + 0x22))) * 2) + arg0)) + 0x19)) = 0;
    callback = (s32 *) 0x08671BB0;
    sub_080C31E4(arg0 + 0x18, arg0 + 0x22, *callback);
  }
}
