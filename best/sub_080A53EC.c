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
M2C_UNK sub_080C31E4();
extern M2C_UNK sub_080A5418;
void sub_080A53EC(void *arg0)
{
  int new_var;
  *((s8 *) (((s8 *) arg0) + 0x6C)) = 0;
  new_var = 0x800 | (*((u16 *) (((s8 *) arg0) + 2)));
  *((u16 *) (((s8 *) arg0) + 2)) = (u16) new_var;
  *((M2C_UNK **) (((s8 *) arg0) + 0x14)) = &sub_080A5418;
  *((s16 *) (((s8 *) arg0) + 0x22)) = 1;
  sub_080C31E4();
}

