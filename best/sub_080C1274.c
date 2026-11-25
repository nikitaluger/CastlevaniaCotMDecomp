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
void sub_080C1274(void *arg0, u16 arg1)
{
  u16 temp_r1;
  u16 new_var;
  new_var = *((u16 *) (((s8 *) arg0) + 0x1C));
  temp_r1 = arg1;
  if ((*((s32 *) (((s8 *) arg0) + 0x34))) == 0x68736D53)
  {
    *((u16 *) (((s8 *) arg0) + 0x1E)) = temp_r1;
    *((s16 *) (((s8 *) arg0) + 0x20)) = (s16) (((s32) (temp_r1 * new_var)) >> 8);
  }
}

